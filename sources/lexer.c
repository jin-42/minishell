#include "../includes/minishell.h"

static void _lstadd(t_token **lst, t_token *new)
{
	t_token *ptr;
	if (!new)
		return ;
	new->next = 0;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
	return ;
}

static t_token *_cp_space(char *s, int *i)
{
	t_token *tok;
	int		j;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	j = *i;
	while (s[j] && s[j] != ' ' && s[j] != '|' 
		&& s[j] != '>' && s[j] != '<' && s[j] != '$') 
		j++;
	tok->str = malloc(sizeof(char) * (j - (*i) + 1));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while (s[(*i)] && s[(*i)] != ' ' && s[(*i)] != '|' 
		&& s[*i] != '>' && s[*i] != '<' && s[*i] != '$')
	{
		tok->str[j] = s[(*i)];
		j++;
		(*i)++;
	}
	tok->str[j] = '\0';
	tok->type = STRING;
	return (tok);
}

static t_token *_cp_var(char *s, int *i)
{
	t_token *tok;
	int		j;
	bool 	flag;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	j = *i;
	flag = false;
	while (s[j] && s[j] != ' ' && s[j] != '|'
		&& s[j] != '>' && s[j] != '<' && s[j] != '$') 
		j++;
	tok->str = malloc(sizeof(char) * (j - (*i) + 1));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while (s[(*i)] && s[(*i)] != ' ' && s[(*i)] != '|'
		&& s[*i] != '>' && s[*i] != '<' && s[*i] != '$')
	{
		if (s[(*i)]  != '\'' && s[(*i)] != '\"')
		{
			tok->str[j] = s[(*i)];
			j++;
			flag = true;
		}
		(*i)++;
	}
	printf("aaaa\n");
	tok->str[j] = '\0';
	tok->type = STRING;
	if (flag == false)
		tok->type = VAR;
	return (tok);
}

static t_token	*_cp_pipe(int *i)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * 3);
	if (!tok->str)
		return (free(tok), NULL);
	tok->str[0] = '|';
	tok->str[1] = '\0';
	tok->type = OP;
	(*i) += 1;
	return (tok);
}

static t_token *_cp_redir(char *s, int *i)
{
    t_token *tok;

   tok = malloc(sizeof(t_token));
    if (!tok)
        return NULL;
    tok->str = malloc(sizeof(char) * 3); // Allocate memory for the string
    if (!tok->str) {
        free(tok);
        return NULL;
    }
    if ((s[*i] == '<') && (s[*i + 1] == '<')) {
        ft_strlcpy(tok->str, "<<", 3);
        (*i)++;
    }
    else if ((s[*i] == '>') && (s[*i + 1] == '>')) {
        ft_strlcpy(tok->str, ">>", 3);
        (*i)++;
    }
    else if (s[*i] == '<') 
        ft_strlcpy(tok->str, "<", 2);
    else 
        ft_strlcpy(tok->str, ">", 2);
    (*i)++;
	tok->type = OP;
    return (tok);
}

static t_token	*_cp_simple_quote(char *s, int *i)
{
	int		j;
	t_token	*tok;

	j = *i;
	while ((s[j] != '\'') && s[j])
		j++;
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * (j - (*i) + 1));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while ((s[*i] != '\'') && s[*i])
	{
		tok->str[j] = s[*i];
		(*i)++;
		j++;
	}
	tok->str[j] = '\0';
	tok->type = STRING;
	return (tok);
}

static t_token	*_cp_double_quote(char *s, int *i)
{
	int	j;
	t_token *tok;

	j = *i;
	while ((s[j] != '\"'))
		j++;
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * (j - (*i) + 1));
	if (!tok->str)
			return (free(tok), NULL);
	j = 0;
	tok->type = STRING;
	while ((s[*i] != '\"'))
	{
		tok->str[j] = s[*i];
		if (tok->str[j] == '$')
			tok->type = VAR_IN_QUOTE;
		(*i)++;
		j++;
		}
	tok->str[j] = '\0';
	return (tok);
}

t_token *lexer(char *s)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			i++;
		else if (s[i] == '\'')
		{
			i++;
			_lstadd(&token, _cp_simple_quote(s, &i));
			i++;
		}
		else if (s[i] == '\"')
		{
			i++;
			_lstadd(&token, _cp_double_quote(s, &i));
			i++;
		}
		else if (s[i] == '<' || s[i] == '>')
		{
			_lstadd(&token, _cp_redir(s, &i));
		}
		// else if (s[i] == '$' && s[i + 1] && s[i + 1] == '\'')
		// {
		// 	i++;
		// 	_lstadd(&token, _cp_var_single_q(s, &i));
		// 	i++;
		// }
		else if (s[i] == '$')
		{
			i++;
			_lstadd(&token, _cp_var(s, &i));
			i++;
		}
		else if (s[i] == '|')
		{
			_lstadd(&token, _cp_pipe(&i));
		}
		else
			_lstadd(&token, _cp_space(s, &i));
	}
	return token;
}

void print_tokens(t_token *tokens) {
    t_token *current = tokens;
	int i = 0;
    
    while (current != NULL) {
        printf("Token: %s\n", current->str);
        printf("Token: %d\n", current->type);
        printf("\n");
        current = current->next;
		i++;
    }
}


/*void _init_block(t_data **data)
{
	(*data) = malloc(sizeof(t_data));
		if (!(*data))
			return ;
	(*data)->block = malloc(sizeof(t_data));
		if (!(*data->block))
			return (free(*data), );
	(*data)->block.builtin = false;
	(*data)->block->path = NULL;
	(*data)->block.int_fd = -2;
	(*data)->block.out_fd = -2;
	(*data)->block.here_doc = false;
}*/

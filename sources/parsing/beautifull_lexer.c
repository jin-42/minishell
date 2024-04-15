# include "../../includes/parsing.h"

static void _lstadd(t_list **lst, t_list *new)
{
	t_list *ptr;
	if (!new)
		return ;
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

static t_list *_cp_space(char *s, int *i)
{
	t_list *tok;
	int		j;

	tok = malloc(sizeof(t_list));
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

static t_list *_cp_var(char *s, int *i)
{
	t_list *tok;
	int		j;

	tok = malloc(sizeof(t_list));
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
	tok->type = VAR;
	return (tok);
}

static t_list	*_cp_pipe(int *i)
{
	t_list	*tok;

	tok = malloc(sizeof(t_list));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * 2);
	if (!tok->str)
		return (free(tok), NULL);
	tok->str[0] = '|';
	tok->str[1] = '\0';
	tok->type = OP;
	(*i) += 1;
	return (tok);
}

static t_list *_cp_redir(char *s, int *i)
{
    t_list *tok;

   tok = malloc(sizeof(t_list));
    if (!tok)
        return NULL;
    tok->str = malloc(sizeof(char) * 3); // Allocate memory for the string
    if (!tok->str) {
        free(tok);
        return NULL;
    }
    if ((s[*i] == '<') && (s[*i + 1] == '<')) {
        strcpy(tok->str, "<<");
        (*i)++;
    }
    else if ((s[*i] == '>') && (s[*i + 1] == '>')) {
        strcpy(tok->str, ">>");
        (*i)++;
    }
    else if (s[*i] == '<') {
        tok->str[0] = '<'; // Assign single character
        tok->str[1] = '\0'; // Null terminate the string
    }
    else {
        tok->str[0] = '>'; // Assign single character
        tok->str[1] = '\0'; // Null terminate the string
    }
    (*i)++;
	tok->type = OP;
    return (tok);
}

static t_list	*_cp_simple_quote(char *s, int *i)
{
	int		j;
	t_list	*tok;

	j = *i;
	while ((s[j] != '\'') && s[j])
		j++;
	tok = malloc(sizeof(t_list));
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

static t_list	*_cp_double_quote(char *s, int *i)
{
	int	j;
	t_list *tok;

	j = *i;
	while ((s[j] != '\"'))
		j++;
	tok = malloc(sizeof(t_list));
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



t_list *_lexer(char *s)
{
	int		i;
	t_list	*token;

	i = 0;
	token = NULL;
	while (s[i])
	{
		while(s[i] == ' ')
			i++;
		if (s[i] == '\'')
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
		else if (s[i] == '$')
		{
			i++;
			_lstadd(&token, _cp_var(s, &i));
		}
		else if (s[i] == '|')
			_lstadd(&token, _cp_pipe(&i));
		else
			_lstadd(&token, _cp_space(s, &i));
	}
	return token;
}

void _print_tokens(t_list *tokens) {
    t_list *current = tokens;
    
    while (current != NULL) {
        printf("Token: %s\n", current->str);
        printf("Token: %d\n", current->type);
        printf("\n");
        current = current->next;
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

int main(int ac, char **av)
{
    t_list *tokens = NULL;
    tokens = _lexer(av[1]);
   _print_tokens(tokens);
   _print_tokens(tokens);
 	//const t_inter *jeudi = _parse(tokens);
   // _print_inter(jeudi);
    return 0;
}

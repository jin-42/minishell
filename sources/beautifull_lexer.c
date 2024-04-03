# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef enum e_bash_op
{
	VAR = 0,
	VAR_IN_QUOTE = 1,
	OP = 2,
	STRING = 3
} e_token_type;

typedef struct s_token
{
	char *str;
	e_token_type type;
	struct s_token *next;
} t_list;



void _lstadd(t_list **lst, t_list *new)
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

t_list *_cp_space(char *s, int *i)
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

t_list *_cp_var(char *s, int *i)
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

t_list	*_cp_pipe(int *i)
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

t_list *_cp_redir(char *s, int *i)
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

t_list	*_cp_simple_quote(char *s, int *i)
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

t_list	*_cp_double_quote(char *s, int *i)
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
			printf("a");
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
    char input[] = "echo  jeudi |$var  \" $hello \"  >> bonjours   >> 'salope  jeudi'";
    t_list *tokens = NULL;
    tokens = _lexer(input);
    _print_tokens(tokens);
    return 0;
}

#include "../includes/minishell.h"

int	_lstadd(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!new)
		return (-1);
	new->next = 0;
	if (!(*lst))
	{
		*lst = new;
		return (0);
	}
	ptr = *lst;
	while (ptr->next != 0)
		ptr = ptr->next;
	ptr->next = new;
	return (0);
}

static t_token	*_space(char *s, int *i)
{
	t_token	*tok;
	int		j;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	j = *i;
	while (s[j] && s[j] != ' ' && s[j] != '|'
		&& s[j] != '>' && s[j] != '<' && s[j] != '\'' && s[j] != '\"') 
		j++;
	tok->str = malloc(sizeof(char) * (j - (*i) + 1));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while (s[(*i)] && s[(*i)] != ' ' && s[(*i)] != '|'
		&& s[(*i)] != '>' && s[(*i)] != '<' && s[(*i)] != '\'' && s[(*i)] != '\"') 
		tok->str[j++] = s[(*i)++];
	tok->str[j] = '\0';
	tok->space = false;
	if (s[(*i)] != '\0' && s[(*i)] == ' ')
		tok->space = true;
	return (tok->type = STRING, tok->quote = false, tok);
}

static t_token	*_pipe(int *i, char *s)
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
	tok->space = false;
	if (s[(*i)] != '\0' && s[(*i)] == ' ')
		tok->space = true;
	return (tok->quote = false, tok);
}

void free_tok(t_token *head)
{
	t_token *current = head;
	t_token *temp;

	while (current != NULL)
	{
		if (current->str)
			free(current->str);
		temp = current;
		current = current->next;
		free(temp);
	}
}

int handle_quote(t_token **token, char *s, int *i)
{
	int flag;

	if (s[*i] == '\'')
	{
		if (s[*i + 1] != '\0' && s[*i + 1] != '\'')
		{
			(*i)++;
			flag = _lstadd(token, simple_quote(s, i));
			(*i)++;
		}
		else
			*i += 2;
	}
	else if (s[*i] == '\"')
	{
		if (s[*i + 1] != '\0')// && s[*i + 1] != '\"')
		{
			(*i)++;
			flag = _lstadd(token, double_quote(s, i));
			(*i)++;
		}
		else
			*i += 2;
	}
	return (flag);
}

t_token	*lexer(char *s)
{
	int		i;
	t_token	*token;
	int flag;

	i = 0;
	token = NULL;
	flag = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ' ')
			i++;
		else if (s[i] == '\'' || s[i] == '\"')
			flag = handle_quote(&token, s, &i);
		else if (s[i] == '<' || s[i] == '>')
			flag = _lstadd(&token, redir(s, &i));
		else if (s[i] == '|')
			flag = _lstadd(&token, _pipe(&i, s));
		else
			flag = _lstadd(&token, _space(s, &i));
		if (flag == -1)
			return (free_tok(token), NULL);
	}
	return (token);
}

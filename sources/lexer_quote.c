#include "../includes/minishell.h"

t_token	*simple_quote(char *s, int *i)
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
		tok->str[j++] = s[(*i)++];
	tok->str[j] = '\0';
	tok->type = QUOTE;
	tok->space = false;
	if (s[(*i + 1)] != '\0' && s[(*i + 1)] == ' ')
		tok->space = true;
	tok->quote = true;
	return (tok);
}

t_token	*double_quote(char *s, int *i)
{
	int		j;
	t_token	*tok;

	j = (*i);
	while ((s[j] != '\"'))
		j++;
	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * (j - (*i) + 1));
	if (!tok->str)
		return (free(tok), NULL);
	j = 0;
	while ((s[*i] != '\"'))
		tok->str[j++] = s[(*i)++];
	tok->type = STRING;
	tok->str[j] = '\0';
	tok->space = false;
	if (s[(*i + 1)] != '\0' && s[(*i + 1)] == ' ')
		tok->space = true;
	tok->quote = true;
	return (tok);
}

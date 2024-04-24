#include "../includes/minishell.h"

int search_env_size(t_data *data, char *name)
{
	t_env	*ptr;
	int		len;

	len = ft_strlen(name);
	if (len == 0)
		return (-1);
	ptr = data->env;
	while (ptr != 0)
	{
		if (ft_strcmp(ptr->name, name) == 0)
			return ((int)(ft_strlen(ptr->val)));
		ptr = ptr->next;
	}
	return (-1);
}

char	*expand_var_in_quote_name(t_token *tok)
{
	int		i;
	char	*name;
	char	*var;
	int		j;

	j = 0;
	name = ft_strchr(tok->str, '$');
	if (name == NULL || ft_strlen(name) == 1)
		return (NULL);
	i = name - tok->str + 1;
	while (tok->str[i] && is_charset(tok->str[i], EXP_CHAR) == 1)
	{
		i++;
		j++;
	}
	var = malloc (sizeof (char) * (j + 1));
	if (!var)
		return (NULL);
	ft_strlcpy(var, name + 1, j + 1);
	return (var);
}

char	*expand_var_in_quote_copy(t_data *data, t_token *tok, char *new, char *name)
{
	int		i;
	int		j;

	ft_strlcpy(new, tok->str, ft_strchr(tok->str, '$') - tok->str + 1);
	i = ft_strlen(new);
	ft_strlcpy(new + i, search_env(data, name), search_env_size(data, name) + 1);
	j = ft_strlen(new);
	i = i + 1 + ft_strlen(name);
	while(tok->str[i])
	{
		new[j] = tok->str[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

void expand_var_in_quote(t_data *data, t_token *tok)
{
	int		size;
	char	*new;
	char	*name;

	size = ft_strlen(tok->str);
	name = expand_var_in_quote_name(tok);
	if (name == NULL)
		return ;
	size = size - ft_strlen(name) - 1 + search_env_size(data, name);
	new = malloc(sizeof (char) * size);
	if (!new)
		return ;
	new = expand_var_in_quote_copy(data, tok, new, name);
	free(name);
	free(tok->str);
	tok->str = new;
	expand_var_in_quote(data, tok);
}

void expand(t_data *data, t_token *head)
{
	int			size_expand;
	char		*tmp;
	t_token		*tok;

	tok = head;
	while (tok)
	{
		if (tok->type == OP && ft_strncmp(tok->str, "<<", 2) == 0)
			tok = tok->next;
		else if (tok->type == VAR)
		{
			size_expand = search_env_size(data, tok->str);
			if (size_expand == -1)
				return (free(tok->str));
			tmp = malloc(sizeof(char) * size_expand);
			if (!tok->str)
				return ; // geston d'erreur ?
			ft_strlcpy(tmp, search_env(data, tok->str), size_expand + 1);
			free(tok->str);
			tok->str = tmp;
		}
		else if (tok->type == VAR_IN_QUOTE)
			expand_var_in_quote(data, tok);
		tok = tok->next;
	}
}

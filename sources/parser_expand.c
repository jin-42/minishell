#include "../includes/minishell.h"

// A REECRIRE QUAND ON AURA GARDE LE $ DEVANT LES VAR

char	*expand_find_name(char *str)
{
	int		i;
	char	*name;
	char	*var;
	int		j;

	j = 0;
	name = ft_strchr(str, '$');
	if (name == NULL || ft_strlen(name) == 1)
		return (NULL);
	i = name - str + 1;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && is_charset(str[i], EXP_CHAR) == 1)
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

char	*expand_copy(t_data *data, t_token *tok, char *new, char *name)
{
	int		i;
	int		j;
	char	*val;

	ft_strlcpy(new, tok->str, ft_strchr(tok->str, '$') - tok->str + 1);
	i = ft_strlen(new);
	if (ft_strcmp(name, "?") == 0)
		val = ft_itoa(data->ret_val);
	else
		val = ft_strdup(search_env(data, name));
	if (!val)
		return (new);
	ft_strlcpy(new + i, val, search_env_size(data, name) + 1);
	free(val);
	j = ft_strlen(new);
	i = i + 1 + ft_strlen(name);
	while (tok->str[i])
	{
		new[j] = tok->str[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

void expand(t_data *data, t_token *tok)
{
	int		size;
	char	*new;
	char	*name;

	size = ft_strlen(tok->str);
	name = expand_find_name(tok->str);
	if (name == NULL)
		return ;
	size = size - ft_strlen(name) - 1 + search_env_size(data, name);
	new = malloc(sizeof (char) * size);
	if (!new)
		return ;
	new = expand_copy(data, tok, new, name);
	free(name);
	free(tok->str);
	tok->str = new;
	expand(data, tok);
}

void	expand_var(t_data *data, t_token *tok)
{
	int			size_expand;
	char		*tmp;
	char		*val;

	size_expand = search_env_size(data, tok->str);
	tmp = malloc(sizeof(char) * size_expand + 1);
	if (!tok->str)
		return ;
	if (ft_strcmp(tok->str, "?") == 0)
		val = ft_itoa(data->ret_val);
	else
		val = ft_strdup(search_env(data, tok->str));
	if (!val)
		return (free(tmp));
	ft_strlcpy(tmp, val, size_expand + 1);
	free(tok->str);
	tok->str = tmp;
}


int findDollarPosition(const char *str) {
    int length;
	int i;
	
	length = ft_strlen(str);
    if (str[0] == '$' && length == 1) 
        return (0);
	if (str[0] == '$' && length != 1)
		return (1);
    if (str[length - 1] == '$')
        return 0;
	i = 0;
   while (i < length) 
   {
        if (str[i] == '$')
            return (2);
		i++;
    }
	return (0);
}

// void	expander(t_data *data, t_token *head)
// {
// 	t_token		*tok;

// 	tok = head;
// 	while (tok)
// 	{
// 		printf("expanding %s\n", tok->str);
// 		if (tok->type == OP && ft_strncmp(tok->str, "<<", 2) == 0)
// 			tok = tok->next;
// 		else if (tok->t)
// 			expand_var(data, tok);
// 		else if (tok->type == VAR_IN_QUOTE)
// 			expand(data, tok);
// 		tok = tok->next;
// 	}
// }

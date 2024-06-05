/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser_expand.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/23 15:49:27 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 13:45:56 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// A REECRIRE QUAND ON AURA GARDE LE $ DEVANT LES VAR

// position du deb du nom = i

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
	while (str[i] && is_charset(str[i], EXP_CHAR) == 1 && i++)
		j++;
	if (j == 0)
	{
		str[i - 1] = -36;
		return (expand_find_name(str));
	}
	var = malloc (sizeof (char) * (j + 1));
	if (!var)
		return (NULL);
	ft_strlcpy(var, name + 1, j + 1);
	return (var);
}

// Copie de ce aui est avant le $
// On se place a la fin de ce qui a ete copie
// Et apres le $NAME
// Copie de ce qui est dans la variable
// On se place de nouveau a la fin de ce qui a ete copie
// On copie ce qui reste dans la str

char	*expand_copy(t_data *data, t_token *tok, char *new, char *name)
{
	int		i;
	int		j;
	char	*val;

	val = search_env(data, name);
	ft_strlcpy(new, tok->str, ft_strchr(tok->str, '$') - tok->str + 1);
	i = ft_strlen(new);
	j = i + 1 + ft_strlen(name);
	if (val != NULL)
	{
		ft_strlcpy(new + i, val, search_env_size(data, name) + 1); 
		i = ft_strlen(new);
	}
	if (ft_strcmp(name, "?") == 0)
		free(val);
	while (tok->str[j])
		new[i++] = tok->str[j++];
	new[i] = 0;
	return (new);
}

void	expand(t_data *data, t_token *tok)
{
	int		size;
	char	*new;
	char	*name;

	size = ft_strlen(tok->str);
	name = expand_find_name(tok->str);
	if (name == NULL)
		return ;
	if (search_env_size(data, name) == -1)
		size = size - ft_strlen(name);
	else
		size = size - ft_strlen(name) + search_env_size(data, name);
	new = malloc(sizeof (char) * size);
	if (!new)
		return ;
	new = expand_copy(data, tok, new, name);
	if (name)
		free(name);
	free(tok->str);
	tok->str = new;
	expand(data, tok);
}

void	untok(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 0)
			str[i] *= -1;
		i++;
	}
}

void	expander(t_data *data, t_token *head)
{
	t_token		*tok;

	tok = head;
	while (tok)
	{
		if (tok->type == STRING)
		{
			if (ft_strlen(tok->str) == 1 && tok->str[0] == '$'
				&& tok->next && tok->next->quote)
			{
				tok->str[0] = '\0';
			}
			else
			{
				expand(data, tok);
				untok(tok->str);
			}
		}
		tok = tok->next;
	}
}

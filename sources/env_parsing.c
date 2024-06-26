/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env_parsing.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/18 16:16:02 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/05/22 12:49:12 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*env_new(char *val, char *name)
{
	t_env	*new;

	new = malloc (sizeof (t_env) * 1);
	if (!new)
	{
		if (val)
			free(val);
		if (name)
			free(name);
		return (NULL);
	}
	new->val = val;
	new->val_len = ft_strlen(val);
	new->name = name;
	new->name_len = ft_strlen(name);
	new->next = NULL;
	return (new);
}

int	env_add_back(t_env **env, t_env *new)
{
	t_env	*ptr;

	ptr = *env;
	if (!new)
		return (1);
	if (*env == 0)
	{
		*env = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return (0);
}

int	parse_paths(t_data *data, bool exec)
{
	char	*path_str;
	char	**path_split;

	if (data->paths != NULL)
		free_full_split(data->paths);
	data->paths = NULL;
	path_split = NULL;
	if (exec == false)
		path_str = getenv("PATH");
	else
		path_str = search_env(data, "PATH");
	if (path_str == NULL)
	{
		data->paths = NULL;
		return (0);
	}
	path_split = ft_split(path_str, ':');
	if (path_split == NULL)
		return (2);
	data->paths = path_split;
	return (0);
}

int	parse_env(t_data *data, char **env)
{
	int		equal;
	int		i;
	char	*val;
	char	*name;

	i = 0;
	equal = 0;
	while (env && env[i])
	{
		val = ft_strchr(env[i], '=') + 1;
		equal = val - 1 - env[i];
		val = ft_strdup(val);
		if (val == NULL)
			return (2);
		name = ft_substr(env[i], 0, equal);
		if (!name)
			return (free(val), 3);
		if (env_add_back(&data->env, env_new(val, name)) != 0)
			return (4);
		i++;
	}
	if (i == 0 && parse_empty_env(data) != 0)
		return (1);
	update_shlvl(data);
	return (0);
}

int	search_env_size(t_data *data, char *name)
{
	t_env	*ptr;
	int		len;

	len = ft_strlen(name);
	if (len == 0)
		return (-1);
	if (ft_strcmp(name, "?") == 0)
		return (number_length(data->ret_val));
	ptr = data->env;
	while (ptr != 0)
	{
		if (ft_strcmp(ptr->name, name) == 0)
			return ((int)(ft_strlen(ptr->val)));
		ptr = ptr->next;
	}
	return (-1);
}

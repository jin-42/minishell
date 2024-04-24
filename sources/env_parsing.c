/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:16:02 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 13:05:54 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
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

int	parse_paths(t_data *data)
{
	char	*path_str;
	char	**path_split;

	if (data->paths != NULL)
		free_full_split(data->paths);
	path_split = NULL;
	path_str = getenv("PATH");
	if (path_str == NULL)
	{
		write(2, "Warning : PATH not set.\n", 24);
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
		val = ft_strdup(val); // Ou enlever si pas besoin d'etre malloc
		if (val == NULL)
			return (2);
		name = ft_substr(env[i], 0, equal);
		if (!name)
			return (free(val), 3);
		if (env_add_back(&data->env, env_new(val, name)) != 0)
			return (4);
		i++;
	}
	if (parse_paths(data) != 0)
		return (5);
	return (0);
}

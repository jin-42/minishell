/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:33:26 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/29 14:38:36 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**append_cmd(char **paths, char *name)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_full_split(paths), NULL);
		free(paths[i]);
		paths[i] = tmp;
		tmp = ft_strjoin(paths[i], name);
		if (!tmp)
			return (free_full_split(paths), NULL);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

int	look_in_env(t_data *data, char **paths)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	data->block->path = NULL;
	while (paths && paths[i])
	{
		if (access(paths[i], X_OK) == 0)
		{
			j = i;
			break ;
		}
		else if (access(paths[i], F_OK) == 0)
			j = i;
		i++;
	}
	if (j != -1)
	{
		data->block->path = ft_strdup(paths[i]);
		if (data->block->path == NULL)
			return (1);
	}
	return (0);
}

int	search_path(t_data *data)
{
	char	**paths;

	if (is_builtin(data) == true)
		return (cpy_builtin(data));
	else if (ft_strchr(data->block->args[0], '/') != NULL)
	{
		if (access(data->block->args[0], F_OK) == SUCCESS)
		{
			data->block->path = ft_strdup(data->block->args[0]);
			if (data->block->path == NULL)
				return (1);
		}
	}
	else
	{
		paths = append_cmd(data->paths, data->block->args[0]);
		if (paths == NULL)
			return (1);
		if (look_in_env(data, paths) != SUCCESS)
			return (free_full_split(paths), 1);
	}
	return (SUCCESS);
}

int	maj_env_paths(t_data *data)
{
	if (data->environ)
		free_env_char(data);
	data->environ = env_to_char(data, false);
	if (data->environ == NULL)
		return (1);
	if (parse_paths(data) != SUCCESS)
		return (free_full_split(data->environ), 2);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:24:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/27 15:48:26 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_builtin(t_data *data)
{
	if (ft_strcmp(data->block->args[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(data->block->args[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(data->block->args[0], "env") == 0)
		return (true);
	else if (ft_strcmp(data->block->args[0], "export") == 0)
		return (true);
	else if (ft_strcmp(data->block->args[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(data->block->args[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(data->block->args[0], "exit") == 0)
		return (true);
	return (false);
}

int	cpy_builtin(t_data *data)
{
	data->block->builtin = true;
	data->block->path = ft_strdup(data->block->args[0]);
	if (data->block->path == NULL)
		return (1);
	return (SUCCESS);
}

void	exec_builtin(t_data *data, char *builtin, char **args)
{
	int	val;

	if (ft_strcmp(data->block->args[0], "cd") == 0)
		val = cd(data, args);
	else if (ft_strcmp(data->block->args[0], "pwd") == 0)
		val = pwd(data, args);
	else if (ft_strcmp(data->block->args[0], "env") == 0)
		val = env(data, args);
	else if (ft_strcmp(data->block->args[0], "export") == 0)
		val = export(data, args);
	else if (ft_strcmp(data->block->args[0], "unset") == 0)
		val = unset(data, args);
	// else if (ft_strcmp(data->block->args[0], "echo") == 0)
	// 	val = echo(data, args);
	// else if (ft_strcmp(data->block->args[0], "exit") == 0)
	// 	val = exit(data, args);
	free_data(data);
	exit(val);
}

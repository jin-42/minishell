/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:24:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/15 14:54:24 by sponthus         ###   ########lyon.fr   */
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

int	exec_builtin(t_data *data, char **args, bool ex)
{
	int	val;

	val = 0;
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
	else if (ft_strcmp(data->block->args[0], "echo") == 0)
		val = bt_echo(data, args + 1);
	else if (ft_strcmp(data->block->args[0], "exit") == 0)
		val = bt_exit(data, args + 1);
	if (ex == true)
		leave_minishell(data, val);
	return (val);
}

int	builtin_process(t_data *data, int i)
{
	// printf("exec builtin \n");
	data->ret_val = 0;
	if (check_builtin_files(data) != 0)
		data->ret_val = 1;
	// printf("determined in_fd = %d / out_fd = %d\n", data->block->in_fd, data->block->out_fd);
	if (dup2(data->block->in_fd, STDIN_FILENO) == -1 && data->ret_val == 0)
	{
		data->ret_val = 1;
		perror("dup2 in: ");
	}
	if (dup2(data->block->out_fd, STDOUT_FILENO) == -1 && data->ret_val == 0)
	{
		data->ret_val = 1;
		perror("dup2 out: ");
	}
	close_all(data, NULL, NULL);
	if (data->ret_val == 0)
		data->ret_val = exec_builtin(data, data->block->args, false);
	next_block(data);
	data->cmd_count = 0;
	return (data->ret_val);
}

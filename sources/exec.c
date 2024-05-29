/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:46:22 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/23 16:49:15 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all(t_data *data, int *old_pipe, int *new_pipe)
{
	t_block	*block;

	block = data->block;
	if (old_pipe)
	{
		if (old_pipe[0] > 2)
			close(old_pipe[0]);
		if (old_pipe[1] > 2)
			close(old_pipe[1]);
	}
	if (new_pipe)
	{
		if (new_pipe[0] > 2)
			close(new_pipe[0]);
		if (new_pipe[1] > 2)
			close(new_pipe[1]);
	}
	while (block)
	{
		if (block->in_fd > 2)
		{
			close(block->in_fd);
			if (block->here_doc == true)
				unlink(block->limiter);
		}
		if (block->out_fd > 2)
			close (block->out_fd);
		block = block->next;
	}
}

void	next_block(t_data *data)
{
	t_block	*block;

	block = data->block->next;
	if (data->block->in_fd > 2)
		close(data->block->in_fd);
	if (data->block->out_fd > 2)
		close(data->block->out_fd);
	if (data->block->path)
		free(data->block->path);
	if (data->block->here_doc == true)
		unlink(data->block->limiter);
	if (data->block->limiter)
		free(data->block->limiter);
	free_full_split(data->block->args);
	free(data->block);
	data->block = block;
}

void	child_process(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	// printf("child no %d - pipes old 0 = %d / old 1 = %d / new 0 = %d / new 1 = %d\n", i, old_pipe[0], old_pipe[1], new_pipe[0], new_pipe[1]);
	if (check_files(data, i, old_pipe, new_pipe) != 0)
	{
		printf("heeeeeeeeere\n");
		error_exec(data, old_pipe, new_pipe, NULL);
	}
	if (search_path(data) != 0)
	{
		printf("HEEEEEERE\n");
		error_exec(data, old_pipe, new_pipe, NULL);
	}
	if (data->block->path == NULL)
	{
		printf("THEREEEEE");
		error_exec(data, old_pipe, new_pipe, "not found");
	}
	// printf("child no %d determined in_fd = %d / out_fd = %d\n", i, data->block->in_fd, data->block->out_fd);
	if (dup2(data->block->in_fd, STDIN_FILENO) == -1)
	{
		// printf("DUPIN SAYS THEEEEEEEERE");
		error_exec(data, old_pipe, new_pipe, "dup2 in:");
	}
	if (dup2(data->block->out_fd, STDOUT_FILENO) == -1)
	{
		// printf("DUPOUT SAYS HEREEEEEEEEE");
		error_exec(data, old_pipe, new_pipe, "dup2 out:");
	}
	close_all(data, old_pipe, new_pipe);
	if (data->block->builtin == true)
	{
		// write(2, "entering\n\n", 9);
		data->ret_val = exec_builtin(data, data->block->args, true);
	}
	else
	{
		// ft_printf_fd(2, "executing %s on %d (ex %d)\n\n", data->block->path, STDIN_FILENO, data->block->in_fd);
		execve(data->block->path, data->block->args, data->environ);
		// ft_printf_fd(2, "IN THE END\n");
		error_exec(data, NULL, NULL, "execve:");
	}
}

void	parent_process(t_data *data, int pid, int *old_pipe, int *new_pipe)
{
	int	status;
	int	w;
	int	value;

	w = 0;
	close_all(data, old_pipe, new_pipe);
	// printf("in the very end\n");
	while (w != -1)
	{
		w = wait(&status);
		if (w == pid)
		{
			if (WIFEXITED(status))
				value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				value = 128 + WTERMSIG(status);
		}
	}
	data->ret_val = value;
	data->cmd_count = 0;
	g_signal = 0;
}

int	exec(t_data *data)
{
	int		old_pipe[2];
	int		new_pipe[2];
	int		i;
	int		fd;

	g_signal = 1;
	if (maj_env_paths(data) != 0 || data->cmd_count == 0)
		return (1);
	i = 0;
	if (data->cmd_count == 1 && is_builtin(data) == true)
	{
		// write(2, "hey\n", 4);
		return (builtin_process(data, i));
	}
	pipe_initializer(old_pipe, new_pipe);
	while (i < data->cmd_count)
	{
		pipe(new_pipe);
		fd = fork();
		if (fd == 0)
			child_process(data, i, old_pipe, new_pipe);
		next_block(data);
		pipe_manager(old_pipe, new_pipe);
		i++;
	}
	parent_process(data, fd, old_pipe, new_pipe);
	// close_all(data, old_pipe, new_pipe);
	// data->cmd_count = 0;
	return (0);
}

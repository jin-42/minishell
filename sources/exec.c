/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:46:22 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/17 11:44:00 by sponthus         ###   ########lyon.fr   */
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
	// if (data->block->limiter)
	// 	free(data->block->limiter);
	// free_full_split(data->block->args);
	// free(data->block);
	data->block = block;
}

void	child_process(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	printf("child no %d - pipes old 0 = %d / old 1 = %d / new 0 = %d / new 1 = %d\n", i, old_pipe[0], old_pipe[1], new_pipe[0], new_pipe[1]);
	if (check_files(data, i, old_pipe, new_pipe) != 0)
	{
		// printf("heeeeeeeeere\n");
		error_exec(data, old_pipe, new_pipe, NULL);
	}
	if (search_path(data) != 0)
	{
		// printf("HEEEEEERE\n");
		error_exec(data, old_pipe, new_pipe, NULL);
	}
	if (data->block->path == NULL)
	{
		// printf("THEREEEEE");
		error_exec(data, old_pipe, new_pipe, "not found");
	}
	printf("determined in_fd = %d / out_fd = %d\n", data->block->in_fd, data->block->out_fd);
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
		exec_builtin(data, data->block->args, true);
	else
	{
		printf("executing %s on %d\n", data->block->path, STDIN_FILENO);
		execve(data->block->path, data->block->args, data->environ);
		// printf("IN THE END\n");
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
}

int	exec(t_data *data)
{
	int		old_pipe[2];
	int		new_pipe[2];
	int		i;
	int		fd;

	if (maj_env_paths(data) != 0)
		return (1);
	i = 0;
	if (data->cmd_count == 1 && is_builtin(data) == true)
		return (builtin_process(data, i));
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
	return (0);
}

// void	exec(t_data *data)
// {
// 	int	pipe[2];
// 	int	i;
// 	int	fd;
// 	int	tmpin;
// 	int	tmpout;

// 	tmpin = dup(STDIN_FILENO);
// 	tmpout = dup(STDOUT_FILENO);
// 	i = 0;
// 	if (data->block->in_fd == -2)
// 		data->block->in_fd = dup(tmpin);
// 	while (i < data->cmd_count)
// 	{
// 		dup2(data->block->in_fd, STDIN_FILENO);
// 		if (i == data->cmd_count - 1 && data->block->out_fd == -2)
// 			data->block->out_fd = dup(tmpout);
// 		else
// 		{
// 			pipe(pipe);
// 			data->block->in_fd = pipe[0];
// 			data->block->out_fd = pipe[1];
// 		}
// 		dup2(data->block->out_fd, STDOUT_FILENO);
// 		close(data->block->out_fd);
// 		fd = fork();
// 		if (fd == -1)
// 			return (2);
// 		else if (fd == 0)
// 			child_process(data, pipe);
// 		next_block(data);
// 		i++;
// 	}
// 	dup2(tmpin, STDIN_FILENO);
// 	dup2(tmpout, STDOUT_FILENO);
// 	parent_process(data, fd);
// }
/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/25 13:46:22 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 16:11:27 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_all(t_data *data, int *old_pipe, int *new_pipe)
{
	t_block	*block;

	block = data->block;
	close_pipe(old_pipe);
	close_pipe(new_pipe);
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

	block = NULL;
	if (data->block)
	{
		if (data->block->next)
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
		if (data->block->args)
			free_full_split(data->block->args);
		free(data->block);
	}
	data->block = block;
}

// printf("child no %d - pipes old 0 = %d / old 1 = %d / new 0 = %d 
// new 1 = %d\n", 
//i, old_pipe[0], old_pipe[1], new_pipe[0], new_pipe[1]);
// printf("d->block->args[0] = /%s/", d->block->args[0]);
// printf("path found = /%s/", d->block->path);
// printf("child no %d determined in_fd = %d / out_fd = %d\n", 
// i, d->block->in_fd, d->block->out_fd);

void	child_process(t_data *d, int i, int *old_pipe, int *new_pipe)
{
	signal(SIGINT, signals_child);
	signal(SIGQUIT, signals_child);
	if (!d->block || !d->block->args || !d->block->args[0])
		error_exec(d, old_pipe, new_pipe, "empty");
	if (check_files(d, i, old_pipe, new_pipe) != 0)
		error_exec(d, old_pipe, new_pipe, NULL);
	if (is_a_directory(d->block->args[0]))
		error_exec(d, old_pipe, new_pipe, "is a directory");
	if (d->paths && search_path(d) != 0)
		error_exec(d, old_pipe, new_pipe, NULL);
	if (!d->block->path || d->block->args[0][0] == '\0'
		|| d->block->path[0] == '\0')
		error_exec(d, old_pipe, new_pipe, "not found");
	if (dup2(d->block->in_fd, STDIN_FILENO) == -1)
		error_exec(d, old_pipe, new_pipe, "dup2 in:");
	if (dup2(d->block->out_fd, STDOUT_FILENO) == -1)
		error_exec(d, old_pipe, new_pipe, "dup2 out:");
	close_all(d, old_pipe, new_pipe);
	if (d->block->builtin == true)
		d->ret_val = exec_builtin(d, d->block->args, true);
	else
	{
		execve(d->block->path, d->block->args, d->environ);
		error_exec(d, NULL, NULL, "execve:");
	}
}

void	parent_process(t_data *data, int pid, int *old_pipe, int *new_pipe)
{
	int	status;
	int	w;
	int	value;

	w = 0;
	close_all(data, old_pipe, new_pipe);
	while (w != -1)
	{
		w = wait(&status);
		if (w == pid)
		{
			if (WIFEXITED(status))
				value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				signals_child(WTERMSIG(status));
				value = 128 + WTERMSIG(status);
				if (WTERMSIG(status) == SIGQUIT)
					write(2, "Quit (core dumped)\n", 19);
			}
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

	if (maj_env_paths(data) != 0 || data->cmd_count == 0)
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	parent_process(data, fd, old_pipe, new_pipe);
	return (0);
}

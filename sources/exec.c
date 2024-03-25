/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:46:22 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/25 17:38:27 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_file(t_data *data) // ferme le programme en erreur

search_path(t_data *data)
{
	
}

void	child_process(t_data *data, int i, int *pipe)
{
	// if (data->block->in_fd == -1 || data->block->out_fd == -1)
	// 	error_file(data, pipe);
	// if (search_path(data) == -1)
	// 	error_path(data, pipe);
	// if (data->block->in_fd == -2 && i != 0)
	// 	if (dup2(pipe[0], STDIN_FILENO) == -1)
	// 		error_dup2(data, pipe);
	// if (data->block->out_fd == -2 && i != data->cmd_count - 1)
	// 	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	// 		error_dup2(data, pipe);
	
	
}

void	pipe_manager(int *old_pipe, int *new_pipe)
{
	if (old_pipe[0])
		close(old_pipe[0]);
	if (old_pipe[1])
		close(old_pipe[1]);
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
}

void	exec(t_data *data)
{
	int	old_pipe[2];
	int	new_pipe[2];
	int	i;
	int	fd;

	i = 0;
	while (i < cmd_count)
	{
		pipe(new_pipe);
		fd = fork();
		if (fd == 0)
		{
			dup2(new_pipe[0], STDOUT_FILENO);
			if (old_pipe[1])
			{
				dup2(old_pipe[1], STDIN_FILENO);
				close(old_pipe[0]);
			}
			close(new_pipe[1]);
			//execve
		}
		pipe_manager(&old_pipe, &new_pipe);
		i++;
	}
	parent_process(data, fd);
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

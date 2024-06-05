/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_pipes.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/27 15:32:52 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/03/27 15:35:45 by sponthus		 ###   ########lyon.fr   */
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

void	close_pipe(int *pipe)
{
	if (pipe)
	{
		if (pipe[0] > 2)
			close(pipe[0]);
		if (pipe[1] > 2)
			close(pipe[1]);
	}
}

void	pipe_manager(int *old_pipe, int *new_pipe)
{
	if (old_pipe[0] > 2)
		close(old_pipe[0]);
	if (old_pipe[1] > 2)
		close(old_pipe[1]);
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
}

void	pipe_initializer(int *old_pipe, int *new_pipe)
{
	old_pipe[0] = -2;
	old_pipe[1] = -2;
	new_pipe[0] = -2;
	new_pipe[1] = -2;
}

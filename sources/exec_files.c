/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:33:03 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 15:39:55 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_infile(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	if (i == 0)
	{
		if (data->block->in_fd == -2)
			data->block->in_fd = 0;
	}
	else
	{
		if (data->block->in_fd == -2)
			data->block->in_fd = old_pipe[0];
		else
			if (isatty(data->block->in_fd) == 1) // On a ouvert un terminal
				data->block->in_fd = -2;
	}
	if (data->block->here_doc == true)
		here_doc(data);
}

void	child_outfile(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	if (i == data->cmd_count - 1)
	{
		if (data->block->out_fd == -2)
			data->block->out_fd = 1;
	}
	else
	{
		if (data->block->out_fd == -2)
			data->block->out_fd = new_pipe[1];
	}
}

int	check_files(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	child_infile(data, i, old_pipe, new_pipe);
	child_outfile(data, i, old_pipe, new_pipe);
	if (data->block->in_fd == -1 || data->block->in_fd == -2)
		return (1);
	if (data->block->out_fd == -1 || data->block->out_fd == -2)
		return (1);
	return (SUCCESS);
}

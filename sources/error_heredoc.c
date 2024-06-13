/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:03:48 by sponthus          #+#    #+#             */
/*   Updated: 2024/06/13 12:09:04 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_filling_heredoc(t_data *data, t_block *block, int fd, char *name)
{
	block->limiter = name;
	block->in_fd = -2;
	close(fd);
	if (g_signal == 130)
		return (130);
	write(2, "Error: expanding heredoc\n", 25);
	return (2);
}

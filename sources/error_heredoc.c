/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   error_heredoc.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/13 12:03:48 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/17 11:03:19 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_heredoc(t_block *block)
{
	write(2, "warning: here-document delimited by end-of-file(wanted `", 56);
	write(2, block->limiter, ft_strlen(block->limiter));
	write(2, "\")\n", 3);
}

int	error_filling_heredoc(t_data *data, t_block *block, int fd, char *name)
{
	(void)data;
	if (block->limiter)
		free(block->limiter);
	block->limiter = name;
	block->in_fd = -2;
	close(fd);
	if (g_signal == 130)
		return (130);
	write(2, "Error: expanding heredoc\n", 25);
	return (2);
}

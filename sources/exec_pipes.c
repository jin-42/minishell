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

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   signals.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/01 15:54:35 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 17:43:16 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// SIGINT = ctrl+C
// SIGQUIT = Ctrl+backslash does nothing
// g_signal allows to know when ctrl+C happened
// else = readline or heredoc
// rl_on_new_line(); = New line
// rl_redisplay(); = gives prompt back

void	signal_init(t_data *data)
{
	signal(SIGINT, signals_parent);
	signal(SIGQUIT, SIG_IGN);
	if (data->ret_val < 0)
		data->ret_val = 0;
}

void	signals_parent(int signal_code)
{
	if (signal_code == SIGINT)
	{
		write(1, "\n", 1);
		g_signal = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_child(int signal_code)
{
	if (signal_code == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		g_signal = 130;
	}
	else if (signal_code == SIGQUIT)
	{
		rl_replace_line("", 0);
		g_signal = 131;
		rl_on_new_line();
	}
}

void	signals_heredoc(int signal_code)
{
	if (signal_code == SIGINT)
	{
		g_signal = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

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
// g_signal allows to know where we are in the program when signal catched
// g_signal = 1 = exec
// else = readline or heredoc
// rl_on_new_line(); = New line
// rl_redisplay(); = gives prompt back

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_signal == 0 || g_signal == -1 || g_signal > 2)
		{
			write(STDIN_FILENO, "^C\n", 3);
			rl_on_new_line();
			rl_redisplay();
			g_signal = -1;
		}
		if (g_signal == 1)
		{
			write(STDIN_FILENO, "\n", 1);
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}

// RL signals gestion off
// redirects signals to signal handler
// Empty masked signals
// SA_RESTART or 0 ? = options, see man sigaction
// SIGINT = Ctrl+Cm SIGQUIT = ctrl+backslask

void	signal_init(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	sa.sa_handler = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; 
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("SIGINT error\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		perror("SIGQUIT error\n");
}

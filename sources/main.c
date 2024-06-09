/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/14 15:54:35 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 17:43:16 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signal;

// void	print_eenv(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		printf("%d =", i);
// 		printf("/%s/\n", env[i]);
// 		i++;
// 	}
// }

t_data	init_data(char **env)
{
	t_data	data;

	data.block = NULL;
	data.cmd_count = 0;
	data.env = NULL;
	data.paths = NULL;
	data.environ = NULL;
	data.ret_val = 0;
	if (parse_env(&data, env) != 0)
		error_parsing(&data, "env");
	return (data);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT) // ctrl C
	{
		if (g_signal == 0 || g_signal == -1 || g_signal > 2) // dans readline
		{
			// write(2, "there\n", 6);
			write(STDIN_FILENO, "^C\n", 3);
			rl_on_new_line(); // Nouvelle ligne
			rl_redisplay(); // Remet le prompt
			g_signal = -1;
		}
		if (g_signal == 1) // On est dans l'exec
		{
			// write(2, "here\n", 5);
			write(STDIN_FILENO, "\n", 1);
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT) // Ctlr backlash ne fait R
	{
		return ;
	}
}

void	signal_init(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0; // Desactive la gestion de signaux de readline
	sa.sa_handler = &signal_handler; // Redirige les signaux vers signal handler
	sigemptyset(&sa.sa_mask); // Vide les signaux masques
	sa.sa_flags = SA_RESTART; // OU 0 ? = options, voir man sigaction
	if (sigaction(SIGINT, &sa, NULL) == -1) // Ctrl C
		perror("SIGINT error\n");
	if (sigaction(SIGQUIT, &sa, NULL) == -1) // Ctlr backslash
		perror("SIGQUIT error\n");
}

char	*input(t_data *data)
{
	char	*line;
	int		ret_val;

	g_signal = 0;
	line = readline("minishell> ");
	if (g_signal == -1)
	{
		data->ret_val = 130;
		g_signal = 0; // Permet de mettre la ret val a 130 apres un ctrl C
	}
	if (!line)
	{
		ret_val = 0;
		free_data(data);
		rl_clear_history();
		write(2, "exit\n", 5);
		exit(ret_val);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	if (quotes_closed(line) == 0)
		return (free(line), NULL); // Add msg error
	return (line);
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	t_data	data;
	t_token *tokens;

	g_signal = 0;
	signal_init();
	data = init_data(environ);
	while (42)
	{
		line = input(&data);
		if (line && line[0] != '\0')
		{
			if (ft_strncmp(line, "stop", 5) == 0)
				break ; // A supprimer quand signaux
			else // On n'en aura pas besoin du else, simplement noter les instructions
			{
				tokens = lexer(line);
				if (!tokens)
				{
					free(line);
					continue;
				}
				print_tokens(tokens);
				replace_escape(tokens);
				expander(&data, tokens);
				tokens = token_join(tokens);
				free(line);
				parser(&data, tokens);
			}
			exec(&data);
		}
		// Signaux
	}
	free_data(&data);
	rl_clear_history();
}

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

// g_signal = 1 = On est dans l'exec
// rl on newline = Nouvelle ligne
// rl_redisplay = Remet le prompt
// Ctlr backlash = SIGQUIT ne fait R
// ctrl C = SIGINT

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
			rl_on_new_line();
			rl_redisplay();
		}
	}
	if (sig == SIGQUIT)
		return ;
}

// Desactive la gestion de signaux de readline
// Redirige les signaux vers signal handler
// Vide les signaux masques
// sa flags -> OU 0 ? = options, voir man sigaction
// Annule Ctrl C
// Annule Ctlr backslash

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

// Gere la mise a 130 du code de retour si ctrl C

char	*input(t_data *data)
{
	char	*line;
	int		ret_val;

	g_signal = 0;
	line = readline("minishell> ");
	if (g_signal == -1)
	{
		data->ret_val = 130;
		g_signal = 0;
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
	line = close_quotes(data, line);
	if (!line)
		return (NULL);
	return (line);
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	t_data	data;
	t_token	*tokens;

	g_signal = 0;
	signal_init();
	data = init_data(environ);
	while (42)
	{
		line = input(&data);
		if (!line)
			continue ;
		if (line && line[0] != '\0')
		{
			tokens = lexer(line);
			// print_tokens(tokens);
			expander(&data, tokens);
			tokens = token_join(tokens);
			parser(&data, tokens);
		}
		if (line)
			free(line);
		exec(&data);
	}
	free_data(&data);
	rl_clear_history();
}

// int	main(int argc, char **argv, char **environ)
// {
// 	// char	*line;
// 	// t_data	data;
// 	// char	*a = "echo";
// 	// char	*b = "cat";
// 	// // char	*c = "blabla";
// 	// char	*end = NULL;
// 	// char	*arg_a[2];
// 	// char	*arg_b[2];
// 	// // char	**arg;
// 	// t_block	block_a;
// 	// t_block	block_b;

// 	// block_a.in_fd = open("/dev/urandom", O_RDONLY);
// 	// block_a.out_fd = -2;
// 	// block_a.here_doc = false;
// 	// block_a.hd_quote = true;
// 	// block_a.limiter = "stop";
// 	// block_a.path = NULL;
// 	// arg_a[0] = a;
// 	// // arg_a[1] = c;
// 	// arg_a[1] = end;
// 	// block_a.args = argv + 1; //arg_a;
// 	// block_a.next = NULL; // &block_b;
// 	// block_a.builtin = false;

// 	// block_b.in_fd = -2;
// 	// block_b.out_fd = -2;
// 	// block_b.here_doc = false;
// 	// block_b.path = NULL;
// 	// arg_b[0] = b;
// 	// // arg_b[1] = c;
// 	// arg_b[1] = end;
// 	// block_b.args = arg_b;
// 	// block_b.next = NULL;
// 	// block_b.builtin = false;

// 	// data = init_data(environ);
// 	// data.block = &block_a;
// 	// data.cmd_count = 1;
// 	// data.ret_val = 0;

// 	// print_data(&data);
// 	// printf("WAITING 3nl\n\n\n");
	
// 	// arg_a[0] = a;
// 	// // arg_a[1] = c;
// 	// arg_a[1] = end;
// 	// // env(&data, arg_a);

// 	// exec(&data);

// 	// env(&data, arg_a);
// 	// val = getcwd(NULL, 0);
// 	// if (val == NULL)
// 	// {
// 	// 	perror("pwd: ");
// 	// 	return (1);
// 	// }
// 	// printf("%s\n", val);
// 	// free(val);


// 	// printf("WAITING 3nl\n\n\n");
// 	// print_data(&data);
// 	// while (42)
// 	// {
// 	// 	line = readline("minishell> ");
// 	// 	if (line)
// 	// 	{
// 	// 		add_history(line);
// 	// 		if (ft_strncmp(line, "stop", 5) == 0)
// 	// 			break ;
// 	// 		else {
// 	// 			t_list	*tokens = lexer(line);
// 	// 			print_parse(tokens);
// 	// 		}
// 	// 		free(line);
// 	// 	}
// 	// }
// 	// free(line);
// 	// free_data(&data);
// 	// rl_clear_history();
// }

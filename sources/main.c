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
	signal_init(&data);
	return (data);
}

char	*input(t_data *data)
{
	char	*line;

	line = readline("minishell> ");
	if (g_signal == 130)
	{
		data->ret_val = 130;
		g_signal = 0;
	}
	if (!line)
	{
		free_data(data);
		rl_clear_history();
		write(2, "exit\n", 5);
		exit(data->ret_val);
	}
	line = close_quotes(data, line);
	if (line && ft_strlen(line) > 0)
		add_history(line);
	if (!line)
		return (NULL);
	return (line);
}

int	update_data_from_line(t_data *data, char *line)
{
	t_token	*tokens;

	tokens = lexer(line);
	if (!tokens)
	{
		free(line);
		write(2, "Error: lexer\n", 13);
		return (1);
	}
	replace_escape(tokens);
	expander(data, tokens);
	tokens = token_join(tokens);
	parser(data, tokens);
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (write(2, "Error: no args required\n", 24), 1);
	g_signal = 0;
	data = init_data(environ);
	while (42)
	{
		signal_init(&data);
		line = input(&data);
		if (line && line[0] != '\0')
		{
			if (update_data_from_line(&data, line) != 0)
				data.ret_val = 1;
			else
				exec(&data);
		}
	}
	free_data(&data);
	rl_clear_history();
}

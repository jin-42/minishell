/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/15 18:04:26 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

// void	print_data(t_data *data)
// {
// 	printf("")
// }

void	print_eenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%d =", i);
		printf("/%s/\n", env[i]);
		i++;
	}
}

t_data	init_data(char **env)
{
	t_data	data;

	data.block = NULL;
	data.cmd_count = 0;
	data.env = NULL;
	data.paths = NULL;
	data.environ = NULL;
	if (parse_env(&data, env) != 0)
		error_parsing(&data, "env");
	return (data);
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	t_data	data;
	t_token *tokens;

	data = init_data(environ);
	while (42)
	{
		line = readline("minishell> ");
		if (line)
		{
			add_history(line);
			if (quotes_closed(line) == 0)
			{
				free(line); // + msg erreur
				continue ;
			}
			if (ft_strncmp(line, "stop", 5) == 0)
				break ; // A supprimer quand signaux
			else // On n'en aura pas besoin du else, simplement noter les instructions
			{
				tokens = lexer(line);
				print_tokens(tokens); // A suppr
				parser(&data, tokens);
				//print_tokens(tokens); // A suppr
			}
			free(line);
			exec(&data);
		}
		// print_data(&data);
		// Signaux
	}
	// free(line);
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
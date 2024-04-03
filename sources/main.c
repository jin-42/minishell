/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 11:18:57 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

void	print_data(t_data *data);

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
	// char	*line;
	t_data	data;
	char	*a = "pwd";
	char	*b = "ls";
	char	*end = NULL;
	char	*arg_a[2];
	char	*arg_b[2];
	// char	**arg;
	t_block	block_a;
	t_block	block_b;

	block_a.in_fd = -2; //open("test", O_RDONLY);
	block_a.out_fd = -2;
	block_a.here_doc = false;
	block_a.path = NULL;
	arg_a[0] = a;
	arg_a[1] = end;
	block_a.args = arg_a;
	block_a.next = NULL; //&block_b;
	block_a.builtin = false;

	block_b.in_fd = -2;
	block_b.out_fd = -2;
	block_b.here_doc = false;
	block_b.path = NULL;
	arg_b[0] = b;
	arg_b[1] = end;
	block_b.args = arg_b;
	block_b.next = NULL;
	block_b.builtin = false;

	data = init_data(environ);
	data.block = &block_a;
	data.cmd_count = 1;
	data.ret_val = 0;

	print_data(&data);
	exec(&data);
	print_data(&data);
	// while (42)
	// {
	// 	line = readline("minishell> ");
	// 	if (line)
	// 	{
	// 		add_history(line);
	// 		if (ft_strncmp(line, "stop", 5) == 0)
	// 			break ;
	// 		else
	// 			arg = ft_split(line, ' ');
	// 		free(line);
	// 		// exec(&data, arg);
	// 		free(arg);
	// 	}
	// }
	free_data(&data);
	// rl_clear_history();
}

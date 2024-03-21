/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/21 16:24:51 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

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
	if (parse_env(&data, env) != 0)
		error_parsing(&data, "env");
	return (data);
}

int	main(int argc, char **argv, char **environ)
{
	char	*line;
	t_data	data;
	char	*arg[3];
	char	*str1 = "heyoo";
	char	*str2 = "ZSH=bb";

	arg[0] = str1;
	arg[1] = str2;
	arg[2] = NULL;
	data = init_data(environ);
	// env(&data);
	// unset(&data, "PAGER");
	// env(&data);
	// cd(&data, "");
	// free_full_split(chare);
	export(&data, NULL);
	export(&data, arg);
	// export(&data, NULL);
	free_data(&data);
	// while (42)
	// {
	// 	line = readline("minishell> ");
	// 	if (line)
	// 	{
	// 		add_history(line);
	// 		if (ft_strncmp(line, "stop", 5) == 0)
	// 			break ;
	// 		else if (ft_strncmp(line, "pwd", 4) == 0)
	// 			pwd();
	// 		else
	// 			printf("%s\n", line);
	// 		free(line);
	// 	}
	// }
	// if (line)
	// 	free(line);
	// rl_clear_history();
}

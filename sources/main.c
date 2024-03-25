/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/25 12:04:58 by sponthus         ###   ########lyon.fr   */
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
	char	**arg;

	data = init_data(environ);
	while (42)
	{
		line = readline("minishell> ");
		if (line)
		{
			add_history(line);
			if (ft_strncmp(line, "stop", 5) == 0)
				break ;
			else
				arg = ft_split(line, ' ');
			free(line);
			// exec(&data, arg);
			free(arg);
		}
	}
	if (line)
		free(line);
	free_data(&data);
	rl_clear_history();
}

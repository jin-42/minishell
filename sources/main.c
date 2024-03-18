/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/18 17:13:49 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void	print_env(t_env *env);
int	parse_env(t_data *data, char **env);

int	status;

t_data	*init_data(char **env)
{
	t_data	data;

	data.block = NULL;
	data.cmd_count = 0;
	data.env = NULL;
	data.paths = NULL;
	if (parse_env(&data, env) != 0)
		exit(EXIT_FAILURE);
	printf("hey\n");
	print_env(data.env);
	return (&data);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	*data;

	data = init_data(env);
	while (42)
	{
		line = readline("minishell> ");
		if (line)
		{
			add_history(line);
			if (ft_strncmp(line, "stop", 5) == 0)
				break ;
			else if (ft_strncmp(line, "pwd", 4) == 0)
				pwd();
			else
				printf("%s\n", line);
			free(line);
		}
	}
	if (line)
		free(line);
	rl_clear_history();
}

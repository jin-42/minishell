/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/18 13:45:26 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

int	main(void)
{
	char	*line;
	char	*dir;

	// printf("%d %d", PIPE, GREATER);
	while (42)
	{
		dir = get_dir();
		if (dir == NULL)
			dir = ft_strdup("minishell");
		printf("%s", dir);
		line = readline("> ");
		// if (line)
		// 	add_history(line);
		if (ft_strncmp(line, "stop", 5) == 0)
			break ;
		printf("%s\n", line);
		free(line);
		free(dir);
	}
	if (line)
		free(line);
	rl_clear_history();
}

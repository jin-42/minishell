/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:54:35 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/18 12:46:06 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	status;

char	*get_dir(void)
{
	char	*dir;
	int		size;
	char	*val;

	dir = NULL;
	val = NULL;
	size = 1;
	while (val == NULL)
	{
		dir = malloc((size + 1) * sizeof (char));
		if (!dir)
			return (NULL);
		val = getcwd(dir, size);
		//printf("val = %x, size = %d\n", val, size);
		if (val != NULL)
			break;
		free(dir);
		size++;
	}
	return (dir);
}

int	main(void)
{
	char	*line;
	char	*dir;

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

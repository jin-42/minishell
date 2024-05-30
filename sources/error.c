/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:27 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/30 16:22:41 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*custom_error(char *function, char *arg) // exemple util : perror(custom_error("cd: ", arg));
{
	char	*str;

	str = ft_strjoin(function, arg);
	if (!str)
		return (NULL);
	return (str);
}

void	error_exec(t_data *data, int *old_pipe, int *new_pipe, char *str)
{
	int	value;

	value = -1;
	close_all(data, old_pipe, new_pipe);
	if (str && ft_strcmp(str, "not found") == 0)
	{
		printf("command not found: %s\n", data->block->args[0]);
		value = 127;
	}
	else if (ft_strcmp(str, "is a directory") == 0)
	{
		printf("%s: Is a directory\n", data->block->args[0]);
		value = 126;
	}
	else if (str)
	{
		printf("that's me writing");
		perror(str);
	}
	else if (str == NULL)
	{
		printf("I am the problem");
	}
	leave_minishell(data, value);
}

void	error_parsing(t_data *data, char *type)
{
	free_data(data);
	if (ft_strncmp(type, "env", 4) == 0)
	{
		write(2, "Error parsing env.\n", 19);
	}
	leave_minishell(data, -1);
	// exit(EXIT_FAILURE);
}

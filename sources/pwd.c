/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:34:32 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/21 16:47:05 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(t_data *data, char **args) // Fully working
{
	char	*val;
	int		i;

	(void)data;
	val = getcwd(NULL, 0);
	if (val == NULL)
	{
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", val);
	free(val);
	while (args && args[i])
	{
		if (i == 1)
		{
			if (ft_strchr(args[i], '-') != NULL)
				printf("pwd: %s: invalid option\n", args[i]);
		}
		i++;
	}
	return (0);
}

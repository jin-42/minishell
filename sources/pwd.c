/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:34:32 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/28 15:27:39 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// A check depuis les ajouts des args
// prend en compte arg[0] = pwd

int	pwd(t_data *data, char **args)
{
	char	*val;
	int		i;

	i = 0;
	(void)data;
	while (args && args[i])
	{
		if (i == 1)
		{
			if (ft_strchr(args[i], '-') != NULL)
				return (printf("pwd: %s: invalid option\n", args[i]), 1);
		}
		i++;
	}
	val = getcwd(NULL, 0);
	if (val == NULL)
	{
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", val);
	free(val);
	return (0);
}

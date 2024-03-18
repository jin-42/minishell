/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:34:32 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/18 16:15:38 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(void)
{
	char	dir[PATH_MAX];
	char	*val;

	val = NULL;
	val = getcwd(dir, PATH_MAX);
	if (val == NULL)
	{
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", dir);
	return (0);
}

// char	*get_dir(void)
// {
// 	char	*dir;
// 	int		size;
// 	char	*val;

// 	dir = NULL;
// 	val = NULL;
// 	size = 1;
// 	while (val == NULL)
// 	{
// 		dir = malloc((size + 1) * sizeof (char));
// 		if (!dir)
// 			return (NULL);
// 		val = getcwd(dir, size);
// 		if (val != NULL)
// 			break;
// 		free(dir);
// 		size++;
// 	}
// 	return (dir);
// }

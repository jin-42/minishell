/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:53:34 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/20 14:12:20 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" // utiliser chdir

int	cd(t_data *data, char *path)
{
	// pwd(); // A retirer
	if (ft_strlen(path) == 0)
	{
		path = search_env(data, "HOME");
		if (path == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
	}
	if (chdir(path) != 0)
		perror("cd");
	// MAJ du OLDPATH a ajouter
	// pwd(); // A retirer
	return (0);
}

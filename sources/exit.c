/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:27 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/20 14:50:53 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env *env) // Ne pas free val, pas malloc
{
	t_env	*ptr;
	t_env	*tmp;

	if (!env)
		return ;
	ptr = env;
	while (ptr)
	{
		tmp = ptr->next;
		if (ptr->name)
			free(ptr->name);
		if (ptr->val)
			free(ptr->val);
		free(ptr);
		ptr = tmp;
	}
	env = NULL;
}

void	free_data(t_data *data) // Ajouter blocks quand seront ajoutes
{
	if (data->env)
		free_env(data->env);
	if (data->paths)
		free_full_split(data->paths);
}

void	error_parsing(t_data *data, char *type)
{
	free_data(data);
	if (ft_strncmp(type, "env", 4) == 0)
	{
		write(2, "Error parsing env.\n", 19);
	}
	exit(EXIT_FAILURE);
}

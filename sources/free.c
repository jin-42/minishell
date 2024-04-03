/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:07:31 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 11:19:09 by sponthus         ###   ########lyon.fr   */
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
	if (data->environ)
		free_full_split(data->environ);
	while (data->block)
		next_block(data); // ferme les FD ouverts
}

void	leave_minishell(t_data *data, int val)
{
	free_data(data);
	if (val > 0)
		exit(val);
	else
		exit(EXIT_FAILURE);
	// rl_clear_history();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:07:31 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/16 14:56:57 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_char(t_data *data)
{
	int	size;
	int	i;
	char	**environ;

	environ = data->environ;
	if (!environ)
		return ;
	i = 0;
	size = env_size(data);
	while (i < size)
	{
		free(environ[i]);
		i++;
	}
	free(data->environ);
}

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
	if (data->environ)
		free_env_char(data);
	if (data->env)
		free_env(data->env);
	if (data->paths)
		free_full_split(data->paths);
	while (data->block)
		next_block(data); // ferme les FD ouverts
}

void	leave_minishell(t_data *data, int val)
{
	free_data(data);
	rl_clear_history();
	if (val >= 0)
		exit(val);
	else
		exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:11:27 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/27 15:32:01 by sponthus         ###   ########lyon.fr   */
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
		next_block(data);
}

void	error_exec(t_data *data, int *old_pipe, int *new_pipe, char *str)
{
	int	value;

	value = 0;
	close_all(data, old_pipe, new_pipe);
	if (str && ft_strcmp(str, "not found") == 0)
	{
		printf("command not found: %s\n", data->block->args[0]);
		value = 127;
	}
	else if (str)
	{
		perror(str);
	}
	free_data(data);
	if (value != 0)
		exit(value);
	else
		exit(EXIT_FAILURE);
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

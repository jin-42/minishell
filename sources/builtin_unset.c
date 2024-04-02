/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:06:46 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/26 11:04:38 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Prend en compte arg[0] = unset
// verifier maintenant que traite une liste, marche pour 1 arg
// Securiser le fait de vider l'environnement

void	env_delone(t_data *data, t_env *node)
{
	t_env	*tmp;
	t_env	*env;

	env = data->env;
	while (env)
	{
		tmp = env;
		if (env == node)
		{
			data->env = env->next;
			break ;
		}
		if (env->next == node)
		{
			env = env->next;
			tmp->next = env->next;
			break ;
		}
		env = env->next;
	}
	if (env->val)
		free(env->val);
	if (env->name)
		free(env->name);
	free(env);
}

t_env	*search_env_node(t_env *env, char *name)
{
	int		len;

	len = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->name, name, len + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	unset(t_data *data, char **args)
{
	t_env	*node;
	int		i;

	i = 1;
	if (!args)
	{
		write(2, "unset: not enough arguments\n", 28);
		return (1);
	}
	while (args[i])
	{
		if (check_name(args[i], "unset") != 0)
			return (2);
		node = search_env_node(data->env, args[i]);
		if (!node)
			return (3);
		env_delone(data, node);
		i++;
	}
	return (0);
}

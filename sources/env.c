/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:34:38 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/21 13:39:03 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Affiche l'environnement, n'affiche pas les variables sans contenu

int	env(t_data *data)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
	return (0);
}

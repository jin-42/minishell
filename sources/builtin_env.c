/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:34:38 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/04 16:38:47 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Affiche l'environnement, n'affiche pas les variables sans contenu
// Tester l ajout des arguments -> OK a priori

int	env(t_data *data, char **args)
{
	t_env	*env;
	int		i;

	i = 1;
	while (args[i])
	{
		if (i == 1)
			return (printf("env: too many arguments or options\n"), 1);
		i++;
	}
	env = data->env;
	while (env)
	{
		if (env->val)
			printf("%s=%s\n", env->name, env->val);
		env = env->next;
	}
	return (0);
}

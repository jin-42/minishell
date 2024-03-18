/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:16:02 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/18 17:20:19 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(t_env *env) // A RETIRER
{
	int	i;

	i = 0;
	while (env->next != 0)
	{
		printf("List element %d \n\n name /%s/ \nval /%s/\n\n", i, env->name, env->val);
		env = env->next;
		i++;
	}
	printf("List element %d \n\n name /%s/ \nval /%s/\n\n", i, env->name, env->val);
}

t_env	*env_new(char *val, char *name)
{
	t_env	*new;

	new = malloc (sizeof (t_env) * 1);
	if (!new)
		return (NULL);
	new->val = val;
	new->name = name;
	new->next = NULL;
	return (new);
}

int	env_add_back(t_env **env, t_env *new)
{
	t_env	*ptr;

	ptr = *env;
	if (!new)
		return (1);
	if (*env == 0)
	{
		*env = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
	return (0);
}

int	parse_env(t_data *data, char **env)
{
	int		equal;
	int		i;
	char	*val;
	char	*name;

	i = 0;
	equal = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		val = ft_strchr(env[i], '=') + 1;
		if (val == NULL)
			return (2);
		equal = val - 1 - env[i];
		name = ft_substr(env[i], 0, equal);
		if (!name)
			return (3);
		if (env_add_back(&data->env, env_new(val, name)) != 0)
			return (4);
		i++;
	}
	// if (parse_paths(data) != 0)
	// 	return (5);
	return (0);
}

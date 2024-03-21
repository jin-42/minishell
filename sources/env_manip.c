/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:40:50 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/21 15:39:29 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**sort_env(t_data *data)
{
	char	**names;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	names = env_to_char(data, true);
	if (names == NULL)
		return (NULL);
	while(names[i])
	{
		j = 0;
		while (names[j])
		{
			if (ft_strcmp(names[i], names[j]) < 0)
			{
				tmp = names[i];
				names[i] = names[j];
				names[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (names);
}

int	env_size(t_data *data)
{
	int		i;
	t_env	*env;

	env = data->env;
	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	*env_join(t_env *env, bool exp)
{
	char	*res;
	char	*tmp;

	if (exp == true)
		return (env->name);
	res = NULL;
	tmp = ft_strjoin(env->name, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, env->val);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

char	**env_to_char(t_data *data, bool exp) // Utile pour recreer le char** de l'env avant chaque bloc d'exec
{
	char	**res;
	t_env	*env;
	int		i;

	i = 0;
	env = data->env;
	res = ft_calloc((env_size(data) + 1), sizeof (char *));
	if (!res)
		return (NULL);
	while (env)
	{
		res[i] = env_join(env, exp);
		env = env->next;
		i++;
	}
	return (res);
}

char	*search_env(t_data *data, char *name)
{
	t_env	*ptr;
	int		len;

	len = ft_strlen(name);
	ptr = data->env;
	while (ptr != 0)
	{
		if (ft_strncmp(ptr->name, name, len) == 0)
			return (ptr->val);
		ptr = ptr->next;
	}
	return (NULL);
}

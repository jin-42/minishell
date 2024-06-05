/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   env_manip.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/21 11:40:50 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/05/22 12:47:46 by sponthus		 ###   ########lyon.fr   */
/*																			*/
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
	while (names[i])
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
	if (env->val && ft_strlen(env->val) > 0)
	{
		res = ft_strjoin(tmp, env->val);
		free(tmp);
		if (!res)
			return (NULL);
	}
	else
		res = tmp;
	return (res);
}

// Recree char** de l'env avant bloc d'exec
char	**env_to_char(t_data *data, bool exp)
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
		if (env->val == NULL && exp == false)
			env = env->next;
		else
		{
			res[i] = env_join(env, exp);
			env = env->next;
			i++;
		}
	}
	res[i] = 0;
	return (res);
}

char	*search_env(t_data *data, char *name)
{
	t_env	*ptr;
	int		len;

	len = ft_strlen(name);
	if (len == 0)
		return (NULL);
	if (ft_strcmp(name, "?") == 0)
		return (ft_itoa(data->ret_val));
	ptr = data->env;
	while (ptr != 0)
	{
		if (ft_strcmp(ptr->name, name) == 0)
			return (ptr->val);
		ptr = ptr->next;
	}
	return (NULL);
}

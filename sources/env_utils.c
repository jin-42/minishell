/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:34:56 by sponthus          #+#    #+#             */
/*   Updated: 2024/06/12 18:16:40 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*search_env_node(t_env *env, char *name)
{
	int		len;

	len = ft_strlen(name);
	if (len == 0)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	update_shlvl(t_data *data)
{
	t_env	*shlvl;
	int		val;
	char	*new;

	shlvl = search_env_node(data->env, "SHLVL");
	if (!shlvl)
	{
		write(2, "SHLVL not found, not updated\n", 29);
		return ;
	}
	val = ft_atoi(shlvl->val);
	val++;
	new = ft_itoa(val);
	if (!new)
	{
		write(2, "Error: itoa SHLVL\n", 18);
		return ;
	}
	free(shlvl->val);
	shlvl->val = new;
}

int	parse_empty_env(t_data *data)
{
	char	*pwd;
	char	*shlvl;

	shlvl = ft_strdup("SHLVL");
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd: ");
		return (1);
	}
	if (env_add_back(&data->env, env_new(pwd, ft_strdup("PWD"))) != 0)
		return (free(pwd), write(2, "Error: parsing env\n", 19), 1);
	if (env_add_back(&data->env, env_new(ft_strdup("0"), shlvl)) != 0)
		return (write(2, "Error: parsing env\n", 19), 1);
	return (0);
}

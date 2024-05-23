/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:45:59 by sponthus          #+#    #+#             */
/*   Updated: 2024/05/23 15:46:58 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var_name(char *name, char *f)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) == 1 || ft_strlen(name) == 0)
	{
		printf("%s: `%s': not a valid identifier\n", f, name);
		return (1);
	}
	while (name[i])
	{
		if (ft_strchr(EXP_CHAR, name[i]) == NULL)
			return (printf("%s: `%s': not a valid identifier\n", f, name), 1);
		i++;
	}
	return (0);
}

int	export_replace_val(t_env *node, char *name, char *val, bool add)
{
	char	*tmp;

	if (add == false)
	{
		free(node->val);
		node->val = val;
	}
	else
	{
		tmp = ft_strjoin(node->val, val);
		if (!tmp)
		{
			free(name);
			free(val);
			return (1);
		}
		free(node->val);
		node->val = tmp;
	}
	node->val_len = ft_strlen(val);
	free(name);
	return (0);
}

int	export_print(t_data *data)
{
	char	**names;
	t_env	*env;
	int		i;

	i = 0;
	names = sort_env(data);
	if (names == NULL)
		return (1);
	while (names[i])
	{
		env = search_env_node(data->env, names[i]);
		printf("declare -x %s", env->name);
		if (env->val)
			printf("=\"%s\"\n", env->val);
		else
			printf("\n");
		i++;
	}
	free(names);
	return (0);
}
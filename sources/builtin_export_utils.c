/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_export_utils.c							 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/23 15:45:59 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 17:41:44 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var_name(char *name, char *val, char *f)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) == 1 || ft_strlen(name) == 0)
	{
		if (val)
			printf("%s: `%s=%s': not a valid identifier\n", f, name, val);
		else
			printf("%s: `%s': not a valid identifier\n", f, name);
		return (1);
	}
	while (name[i])
	{
		if (ft_strchr(EXP_CHAR, name[i]) == NULL)
		{
			if (val)
				printf("%s: `%s=%s': not a valid identifier\n", f, name, val);
			else
				printf("%s: `%s': not a valid identifier\n", f, name);
			return (1);
		}
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
		if (node->val)
			tmp = ft_strjoin(node->val, val);
		else
			tmp = ft_strdup(val);
		if (!tmp)
			return (free(val), free(name), 1);
		free(node->val);
		free(val);
		node->val = tmp;
	}
	node->val_len = ft_strlen(node->val);
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

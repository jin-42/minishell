/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_export.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/20 16:35:12 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 16:50:35 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// Without options : shows env in ASCII order with variables without value
// Puts "" around value
// Wth option : adds option to env
// If SPACE = creates var with name and value
// If NO SPACE = Adds var with NULL value (so no VAR="")
// If + SPACE = Adds value to the var value or creates it if doesnt exist
// If several args = Treats every arg individually
// Accepts only 1st caract to be alpha or UNIX, not a number

// WARNING : arg[0] = export
// checks ok

int	export_apply(t_data *data, char *name, char *val, bool add)
{
	t_env	*env_node;

	env_node = search_env_node(data->env, name);
	if (env_node)
	{
		if (export_replace_val(env_node, name, val, add) != 0)
			return (1);
	}
	else
	{
		if (check_var_name(name, val, "export") == 0)
			return (env_add_back(&data->env, env_new(val, name)));
		else
		{
			free(name);
			free(val);
			return (1);
		}
	}
	return (0);
}

char	*export_find_name(char *arg, char *equal, bool add, bool val)
{
	char	*name;

	if (val == true)
	{
		if (add == true)
			name = ft_substr(arg, 0, equal - arg - 1);
		else
			name = ft_substr(arg, 0, equal - arg);
		if (!name)
			return (NULL);
	}
	if (val == false)
	{
		name = ft_strdup(arg);
		if (!name)
			return (NULL);
	}
	return (name);
}

int	export_arg(t_data *data, char *arg)
{
	char	*name;
	char	*val;
	bool	add;

	add = false;
	val = ft_strchr(arg, '=');
	if (val > arg && *(val - 1) == '+')
		add = true;
	if (val != NULL && ft_strlen(arg) > 1 && val != arg)
	{
		name = export_find_name(arg, val, add, true);
		if (!name)
			return (1);
		val = ft_strdup(val + 1);
		if (!val)
			return (free(name), 1);
	}
	else
	{
		name = export_find_name(arg, val, add, false);
		if (!name)
			return (1);
		val = NULL;
	}
	return (export_apply(data, name, val, add));
}

int	export(t_data *data, char **args)
{
	int	i;
	int	val;

	i = 1;
	val = 0;
	while (args[i])
	{
		if (ft_strlen(args[1]) > 1 && args[1][0] == '-')
		{
			args[1][2] = '\0';
			return (printf("export: `%s': invalid option\n", args[1]), 2);
		}
		else if (ft_strchr(args[i], '!'))
		{
			printf("%s: event not found\n",
				args[i] + (ft_strchr(args[i], '!') - args[i]));
			val = 1;
		}
		else if (args[i] && export_arg(data, args[i]) != 0)
			val = 1;
		i++;
	}
	if (i == 1 && export_print(data))
		return (1);
	return (val);
}

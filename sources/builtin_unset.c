/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_unset.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/20 14:06:46 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 16:35:42 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// arg[0] = unset
// Check list of a
// Empty env = checked, ok

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

int	unset(t_data *data, char **a)
{
	t_env	*node;
	int		i;
	int		val;

	i = 1;
	val = 0;
	while (a[i])
	{
		if (ft_strlen(a[1]) > 1 && a[1][0] == '-')
		{
			a[1][2] = '\0';
			return (printf("unset: `%s': invalid option\n", a[1]), 2);
		}
		else if (ft_strchr(a[i], '!')
			|| check_var_name(a[i], NULL, "unset") != 0)
			val = 1;
		if (ft_strchr(a[i], '!'))
			printf("%s: event not found\n",
				a[i] + (ft_strchr(a[i], '!') - a[i]));
		node = search_env_node(data->env, a[i]);
		if (node)
			env_delone(data, node);
		i++;
	}
	return (val);
}

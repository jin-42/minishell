/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/28 11:07:31 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 17:42:36 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env_char(t_data *data)
{
	int		i;
	char	**environ;

	environ = data->environ;
	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		if (environ[i])
			free(environ[i]);
		i++;
	}
	free(data->environ);
}

// Val is not malloc, do not free

void	free_env(t_env *env)
{
	t_env	*ptr;
	t_env	*tmp;

	if (!env)
		return ;
	ptr = env;
	while (ptr)
	{
		tmp = ptr->next;
		if (ptr->name)
			free(ptr->name);
		if (ptr->val)
			free(ptr->val);
		free(ptr);
		ptr = tmp;
	}
	env = NULL;
}

void	free_data(t_data *data)
{
	if (data->environ)
		free_env_char(data);
	if (data->env)
		free_env(data->env);
	if (data->paths)
		free_full_split(data->paths);
	while (data->block)
		next_block(data);
}

// during test don't hesitate to write clear history to prove its exec
// write(2, "clear history\n", 14)'

void	leave_minishell(t_data *data, int val)
{
	free_data(data);
	rl_clear_history();
	if (val >= 0)
		exit(val);
	else
		exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_cd.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/20 12:53:34 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/05/15 15:02:32 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// Check seems ok
// arg[0] = "cd"
// Like bash cd, uses 1 arg exactly not more

char	*search_cd_path(t_data *data, char *arg)
{
	t_env	*home;
	char	*path;

	path = NULL;
	if (ft_strlen(arg) == 0)
	{
		home = search_env_node(data->env, "HOME");
		if (home == NULL || home->val == NULL || home->val[0] == '\0')
		{
			write(2, "cd: HOME not set\n", 17);
			return (NULL);
		}
		else
			path = ft_strdup(home->val);
	}
	else
		path = arg;
	return (path);
}

void	free_pwd_args(char **args)
{
	if (args[0])
		free(args[0]);
	if (args[1])
		free(args[1]);
	if (args[2])
		free(args[2]);
}

int	maj_pwd(t_data *data, char *old_path)
{
	char	*args[4];
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd: ");
		return (1);
	}
	args[0] = ft_strdup("export");
	args[1] = ft_strjoin("OLDPWD=", old_path);
	args[2] = ft_strjoin("PWD=", path);
	args[3] = NULL;
	free(path);
	if (args[0] == NULL || args[1] == NULL || args[2] == NULL)
		return (free_pwd_args(args), 1);
	if (export(data, args) != 0)
		return (free_pwd_args(args), 1);
	free_pwd_args(args);
	return (0);
}

int	cd(t_data *data, char **args)
{
	int		i;
	char	*path;
	char	*error;
	char	old_pwd[PATH_MAX];

	i = 0;
	while (args && args[i])
	{
		if (i == 2)
			return (ft_printf_fd(2, "cd: too many arguments\n"), 1);
		i++;
	}
	path = search_cd_path(data, args[1]);
	if (path == NULL)
		return (1);
	getcwd(old_pwd, PATH_MAX);
	if (chdir(path) != 0)
	{
		error = custom_error("cd: ", path);
		perror(error);
		return (free(error), 1);
	}
	if (maj_pwd(data, old_pwd) != 0)
		return (1);
	return (0);
}

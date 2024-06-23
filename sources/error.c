/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   error.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/20 11:11:27 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 14:48:53 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// ex util : perror(custom_error("cd: ", arg));

char	*custom_error(char *function, char *arg)
{
	char	*str;

	str = ft_strjoin(function, arg);
	if (!str)
		return (NULL);
	return (str);
}

void	error_exec(t_data *data, int *old_pipe, int *new_pipe, char *str)
{
	int	value;

	value = data->ret_val;
	close_all(data, old_pipe, new_pipe);
	if (str && ft_strcmp(str, "not found") == 0)
	{
		ft_printf_fd(2, "%s: command not found\n", data->block->args[0]);
		value = 127;
	}
	else if (str && ft_strcmp(str, "is a directory") == 0)
	{
		ft_printf_fd(2, "%s: Is a directory\n", data->block->args[0]);
		value = 126;
	}
	else if (str && ft_strcmp(str, "empty") == 0)
		value = 0;
	else if (str && ft_strcmp(str, "execve:"))
	{
		ft_printf_fd(2, "%s: %s", str, data->block->args[0]);
		perror("");
	}
	else if (str)
		perror(str);
	leave_minishell(data, value);
}

void	error_parsing(t_data *data, char *type)
{
	free_data(data);
	if (ft_strcmp(type, "env") == 0)
	{
		write(2, "Error parsing env.\n", 19);
	}
	leave_minishell(data, -1);
}

int	error_parser(t_data *data, t_token *tok, int errno)
{
	if (errno > 0)
		free_tok(tok);
	while (data->block)
		next_block(data);
	data->cmd_count = 0;
	if (errno == 2)
		ft_printf_fd(2, "Error: syntax operator\n");
	// else if (errno == 1)
	// 	ft_printf_fd(2, "Error: syntax backslash\n");
	else if (errno == 3)
		ft_printf_fd(2, "Error: allocation\n");
	return (errno);
}

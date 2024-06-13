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

void	error_heredoc(t_block *block)
{
	write(2, "warning: here-document delimited by end-of-file(wanted `", 56);
	write(2, block->limiter, ft_strlen(block->limiter));
	write(2, "\")\n", 3);
}

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

	value = -1;
	close_all(data, old_pipe, new_pipe);
	if (str && ft_strcmp(str, "not found") == 0)
	{
		printf("%s: command not found\n", data->block->args[0]);
		value = 127;
	}
	else if (str && ft_strcmp(str, "is a directory") == 0)
	{
		printf("%s: Is a directory\n", data->block->args[0]);
		value = 127;
	}
	else if (str && ft_strcmp(str, "empty") == 0)
		value = 0;
	else if (str && ft_strcmp(str, "execve:"))
	{
		printf("%s: %s", str, data->block->args[0]);
		perror("");
	}
	else if (str)
		perror(str);
	leave_minishell(data, value);
}

void	error_parsing(t_data *data, char *type)
{
	free_data(data);
	if (ft_strncmp(type, "env", 4) == 0)
	{
		write(2, "Error parsing env.\n", 19);
	}
	leave_minishell(data, -1);
}

void	error_parser(t_token *tok, int errno)
{
	if (errno > 0)
		free_tok(tok);
	if (errno == 1)
		return ((void)ft_printf_fd(2, "Error: syntax operator\n"));
	else if (errno == 2)
		return ((void)ft_printf_fd(2, "Error: syntaxe backslash\n"));
	else
		return ((void)ft_printf_fd(2, "Error: allocation\n"));
}

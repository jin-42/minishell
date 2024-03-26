/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:46:22 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/26 12:52:13 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_file(t_data *data) // ferme le programme en erreur

char	**append_cmd(char **paths, char *name)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_full_split(paths), NULL);
		free(paths[i]);
		paths[i] = tmp;
		tmp = ft_strjoin(paths[i], name);
		if (!tmp)
			return (free_full_split(paths), NULL);
		free(paths[i]);
		paths[i] = tmp;
		i++;
	}
	return (paths);
}

int	exec_builtin() // WIP

int	search_path(t_data *data)
{
	char	**paths;

	// Commncer par chercher si c'est un builtin, si ca en est un, return path = cpy du nom
	paths = append_cmd(data->paths, data->block->args[0]);
	// continue
	return (0);
}

void	child_infile(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	if (i == 0)
	{
		if (data->block->in_fd == -2)
			data->block->in_fd = 0;
	}
	else
	{
		if (data->block->in_fd == -2)
			data->block->in_fd = old_pipe[1];
	}
}

void	child_outfile(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	if (i == data->cmd_count - 1)
	{
		if (data->block->out_fd == -2)
			data->block->out_fd = 1;
	}
	else
	{
		if (data->block->out_fd == -2)
			data->block->out_fd = new_pipe[0];
	}
}

int	check_files(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	child_infile(data, i, old_pipe, new_pipe);
	child_outfile(data, i, old_pipe, new_pipe);
	if (data->block->in_fd == -1 || data->block->out_fd == -1)
		return (1);
}

int	maj_env_paths(t_data *data)
{
	data->environ = env_to_char(data, false);
	if (data->environ)
		return (1);
	if (parse_paths(data) != 0)
		return (free_full_split(data->environ), 0);
	return (0);
}

void	close_all(t_data *data, int *old_pipe, int *new_pipe)
{
	t_block	*block;

	block = data->block;
	if (old_pipe)
	{
		if (old_pipe[0] > 2)
			close(old_pipe[0]);
		if (old_pipe[1] > 2)
			close(old_pipe[1]);
	}
	if (new_pipe)
	{
		if (new_pipe[0] > 2)
			close(new_pipe[0]);
		if (new_pipe[1] > 2)
			close(new_pipe[1]);
	}
	while (block)
	{
		if (block->in_fd > 2)
			close(block->in_fd);
		if (block->out_fd > 2)
			close (block->out_fd);
		block = block->next;
	}
}

void	error_exec(t_data *data, int *old_pipe, int *new_pipe, char *str)
{
	close_all(data, old_pipe, new_pipe);
	if (str)
		perror(str);
	exit(EXIT_FAILURE);
}

int	child_process(t_data *data, int i, int *old_pipe, int *new_pipe)
{
	if (check_files(data, old_pipe, new_pipe) != 0)
		error_exec(data, old_pipe, new_pipe, NULL);
	if (search_path(data) != 0)
		error_exec(data, old_pipe, new_pipe, NULL);
	if (data->block->path == NULL)
		error_exec(data, old_pipe, new_pipe, "not found");
	if (dup2(data->block->in_fd, STDIN_FILENO) == -1)
		error_exec(data, old_pipe, new_pipe, "dup2 in:");
	if (dup2(data->block->out_fd, STDOUT_FILENO) == -1)
		error_exec(data, old_pipe, new_pipe, "dup2 out:");
	close_all(data, old_pipe, new_pipe);
	if (data->block->builtin == true)
		exec_builtin(data, data->block->path, data->block->args);
	else
	{
		execve(data->block->path, data->block->args, data->environ);
		error_exec(data, NULL, NULL, "execve:");
	}
}

void	pipe_manager(int *old_pipe, int *new_pipe)
{
	if (old_pipe[0] > 2)
		close(old_pipe[0]);
	if (old_pipe[1] > 2)
		close(old_pipe[1]);
	old_pipe[0] = new_pipe[0];
	old_pipe[1] = new_pipe[1];
}

void	pipe_initializer(int *old_pipe, int *new_pipe)
{
	old_pipe[0] = -2;
	old_pipe[1] = -2;
	new_pipe[0] = -2;
	new_pipe[1] = -2;
}

void	exec(t_data *data)
{
	int		old_pipe[2];
	int		new_pipe[2];
	int		i;
	int		fd;

	if (maj_env_paths(data) != 0)
		return ;
	i = 0;
	pipe_initializer(old_pipe, new_pipe);
	while (i < cmd_count)
	{
		pipe(new_pipe);
		fd = fork();
		if (fd == 0)
		{
			child_process(data, i, old_pipe, new_pipe);
		}
		pipe_manager(&old_pipe, &new_pipe);
		i++;
	}
	parent_process(data, fd);
}

// void	exec(t_data *data)
// {
// 	int	pipe[2];
// 	int	i;
// 	int	fd;
// 	int	tmpin;
// 	int	tmpout;

// 	tmpin = dup(STDIN_FILENO);
// 	tmpout = dup(STDOUT_FILENO);
// 	i = 0;
// 	if (data->block->in_fd == -2)
// 		data->block->in_fd = dup(tmpin);
// 	while (i < data->cmd_count)
// 	{
// 		dup2(data->block->in_fd, STDIN_FILENO);
// 		if (i == data->cmd_count - 1 && data->block->out_fd == -2)
// 			data->block->out_fd = dup(tmpout);
// 		else
// 		{
// 			pipe(pipe);
// 			data->block->in_fd = pipe[0];
// 			data->block->out_fd = pipe[1];
// 		}
// 		dup2(data->block->out_fd, STDOUT_FILENO);
// 		close(data->block->out_fd);
// 		fd = fork();
// 		if (fd == -1)
// 			return (2);
// 		else if (fd == 0)
// 			child_process(data, pipe);
// 		next_block(data);
// 		i++;
// 	}
// 	dup2(tmpin, STDIN_FILENO);
// 	dup2(tmpout, STDOUT_FILENO);
// 	parent_process(data, fd);
// }

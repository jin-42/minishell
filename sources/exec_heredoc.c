/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:00:42 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/17 11:05:04 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Si heredoc priorite sur le infile

char	*expand_heredoc_copy(t_data *data, char *line, char *new, char *name)
{
	int	i;
	int	j;

	ft_strlcpy(new, line, ft_strchr(line, '$') - line + 1);
	i = ft_strlen(new);
	ft_strlcpy(new + i, search_env(data, name), search_env_size(data, name) + 1);
	j = ft_strlen(new);
	i = i + 1 + ft_strlen(name);
	while (line[i])
	{
		new[j] = line[i];
		i++;
		j++;
	}
	new[j] = 0;
	return (new);
}

char	*expand_heredoc(t_data *data, char *line)
{
	int		size;
	char	*name;
	char	*new;

	if (data->block->hd_quote == true)
		return (line);
	size = ft_strlen(line);
	name = expand_find_name(line);
	if (name == NULL)
		return (line);
	size = size - ft_strlen(name) - 1 + search_env_size(data, name);
	new = malloc(sizeof (char ) * size);
	if (!new)
		return (line);
	new = expand_heredoc_copy(data, line, new, name);
	free(name);
	free(line);
	line = new;
	return (line);
}

int	fill_heredoc(t_data *data, int fd)
{
	char	*line;

	line = NULL;
	// printf("fd = %d", fd);
	while (42) // ou signal de fin capte = 130
	{
		if (line)
			free(line);
		// if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO)) // A rajouter a la fin selon les tests si on redirige err et le minishell dans un fichier
			// line = readline("> "); // ou GNL ?
		line = readline("> ");
		line = expand_heredoc(data, line);
		if (line == NULL)
			return (1);
		if (strcmp(line, data->block->limiter) == 0)
			break ;
		write(fd, line, ft_strlen(line));
	}
	if (line)
		free(line);
	return (0);
}

char	*random_name(void) // prend un nom de 9 carac compose de isAlpha dans urandom
{
	char	*rand;
	int		fd;
	int		i;

	i = 0;
	rand = ft_calloc(10, sizeof(char));
	if (!rand)
		return (NULL);
	fd = open("/dev/urandom", O_RDONLY, 00644);
	if (fd == -1)
		return (NULL);
	if (read(fd, rand, 9) == -1)
		return (NULL);
	close(fd);
	while (rand[i])
	{
		if (rand[i] < 0)
			rand[i] = -rand[i] % 26 + 'a';
		else
			rand[i] = rand[i] % 26 + 'A';
		i++;
	}
	return (rand);
}

int	heredoc(t_data *data)
{
	int		fd;
	char	*name;

	if (data->block->in_fd > 2)
		close(data->block->in_fd);
	name = random_name();
	if (!name)
		return (1);
	fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 00644);
	if (fd < 0)
		return (1);
	if (fill_heredoc(data, fd) < 0)
	{
		data->block->in_fd = -2;
		return (1);
	}
	close(fd);
	fd = open(name, O_RDONLY, 00644);
	if (fd < 0)
		return (1);
	data->block->in_fd = fd;
	if (data->block->limiter)
		free(data->block->limiter);
	data->block->limiter = name;
	return (0);
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   exec_heredoc.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/03 14:00:42 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/05/27 15:22:56 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_heredoc_copy(t_data *data, char *line, char *new, char *name)
{
	int		i;
	int		j;
	char	*val;

	val = search_env(data, name);
	ft_strlcpy(new, line, ft_strchr(line, '$') - line + 1);
	i = ft_strlen(new);
	j = i + 1 + ft_strlen(name);
	if (val != NULL)
	{
		ft_strlcpy(new + i, val, search_env_size(data, name) + 1);
		i = ft_strlen(new);
	}
	while (line[j])
		new[i++] = line[j++];
	new[i] = 0;
	return (new);
}

char	*expand_heredoc(t_data *data, char *line)
{
	int		size;
	char	*new;
	char	*name;

	if (data->block->hd_quote == true)
		return (line);
	size = ft_strlen(line);
	name = expand_find_name(line);
	if (name == NULL)
		return (line);
	if (search_env_size(data, name) == -1)
		size = size - ft_strlen(name);
	else
		size = size - ft_strlen(name) + search_env_size(data, name);
	new = malloc(sizeof (char) * size);
	if (!new)
		return (line);
	new = expand_heredoc_copy(data, line, new, name);
	if (name)
		free(name);
	free(line);
	line = new;
	line = expand_heredoc(data, line);
	return (line);
}

int	fill_heredoc(t_data *data, t_block *block, int fd)
{
	char	*line;

	line = NULL;
	while (42)
	{
		g_signal = fd;
		line = readline("> ");
		if (!line)
		{
			error_heredoc(block);
			break ;
		}
		if (line && strcmp(line, block->limiter) == 0)
			break ;
		line = expand_heredoc(data, line);
		if (line == NULL)
			return (1);
		if (strcmp(line, block->limiter) == 0)
			break ;
		ft_printf_fd(fd, "%s\n", line);
		free(line);
	}
	if (line)
		free(line);
	return (0);
}

// Takes a random name in /dev/urandom made of isAlpha

char	*random_name(void)
{
	char	*rand;
	int		fd;
	int		i;

	i = 0;
	rand = ft_calloc(16, sizeof(char));
	if (!rand)
		return (NULL);
	fd = open("/dev/urandom", O_RDONLY, 00644);
	if (fd == -1)
		return (NULL);
	if (read(fd, rand, 15) == -1)
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
	rand = cpy_no_nt(rand, "/tmp/", 6);
	return (rand);
}

int	heredoc(t_data *data)
{
	int		fd;
	char	*name;
	t_block	*block;

	block = data->block;
	while (block)
	{
		if (data->block->here_doc == true)
		{
			if (block->in_fd > 2)
				close(block->in_fd);
			name = random_name();
			if (!name)
				return (1);
			fd = open(name, O_RDWR | O_TRUNC | O_CREAT, 00644);
			if (fd < 0)
				return (1);
			if (fill_heredoc(data, block, fd) < 0)
			{
				block->limiter = name;
				block->in_fd = -2;
				return (close(fd), 1);
			}
			close(fd);
			fd = open(name, O_RDONLY, 00644);
			if (fd < 0)
				return (1);
			block->in_fd = fd;
			if (block->limiter)
				free(block->limiter);
			block->limiter = name;
		}
		block = block->next;
	}
	return (0);
}

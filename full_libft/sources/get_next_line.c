/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:40:04 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 15:56:44 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	count_lines(int fd)
{
	size_t		nb;
	char		*line;

	nb = 0;
	while (nb == 0 || line)
	{
		line = get_next_line(fd);
		nb++;
		free(line);
	}
	close(fd);
	return (nb - 1);
}

char	*read_while(int fd, char *buf, char *line, int *n)
{
	int	size;

	size = read_file(fd, buf);
	while (size > 0 && *n == 0)
	{
		line = ft_strjoin_free(line, buf, n, size);
		if (line == NULL)
			return (NULL);
		if (size > 0 && *n == 0)
			size = read_file(fd, buf);
	}
	if (size < 0)
	{
		if (line != NULL)
			free(line);
		*n = 0;
		return (NULL);
	}
	return (line);
}

char	*ft_cut(char *line, int *n)
{
	int		size;
	char	*new;

	if (line == NULL)
		return (NULL);
	size = ft_strlen(line);
	new = malloc(size + 1);
	if (new)
	{
		ft_strlcpy_nl(new, line, 0, n);
	}
	if (line)
		free(line);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1] = "\0";
	char		*line;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buf[0] = '\0';
		return (NULL);
	}
	n = 0;
	line = NULL;
	if (buf[0] != '\0')
	{
		line = ft_strjoin_free(line, buf, &n, ft_strlen(buf));
		if (line == NULL)
			return (NULL);
	}
	if (n == 0)
		line = read_while(fd, buf, line, &n);
	ft_buffmove(buf, buf + n, BUFFER_SIZE - n, &n);
	line = ft_cut(line, &n);
	return (line);
}

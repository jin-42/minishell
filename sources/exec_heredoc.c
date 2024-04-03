/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:00:42 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 15:33:53 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// Si heredoc priorite sur le infile

int	fill_heredoc(t_data *data, int fd)
{
	char	*line;

	line = NULL;
	while (42)
	{
		if (line)
			free(line);
		line = readline("> ");
		// if (data->block->hd_quote == false) // expand line si pas de ''
		// 	line = expand(data, line);
		write(fd, line, ft_strlen(line));
		if (strcmp(line, data->block->limiter) != 0)
			break ;
	}
	free(line);
}

int	heredoc(t_data *data)
{
	int	fd;

	fd = OPEN("tmp/here_doc", O_TRUNC, O_CREAT, 00700);
	if (fd == -1)
		return (1);
	fill_heredoc(data, fd);
	data->block->in_fd = fd;
}

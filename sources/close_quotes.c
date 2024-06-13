/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:59:28 by sponthus          #+#    #+#             */
/*   Updated: 2024/06/13 12:08:30 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_quote(t_data *data, char *str, char closed)
{
	char	*line;
	char	*bn;
	char	*res;

	bn = ft_strjoin(str, "\n");
	if (!bn)
		return (free(str), NULL);
	free(str);
	line = readline("> ");
	if (!line)
	{
		data->ret_val = 2;
		ft_printf_fd(2, "unexpected EOF while looking for matching `%c\"\n",
			closed);
		return (free(bn), NULL);
	}
	res = ft_strjoin(bn, line);
	free(bn);
	free(line);
	return (res);
}

char	*close_quotes(t_data *data, char *str)
{
	char	closed;
	char	*line;

	closed = quotes_closed(str);
	if (closed == 0)
		return (str);
	while (closed != 0)
	{
		g_signal = 0;
		line = get_quote(data, str, closed);
		if (!line)
			return (NULL);
		str = line;
		closed = quotes_closed(str);
	}
	return (str);
}

char	quotes_closed(const char *str)
{
	int		i;
	int		res;

	res = 0;
	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			res = str[i];
			i++;
			while (str[i])
			{
				if (str[i] == res)
				{
					res = 0;
					break ;
				}
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (res);
}

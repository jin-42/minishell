/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:38:50 by sponthus          #+#    #+#             */
/*   Updated: 2024/06/05 18:47:35 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// // Initialisation de la pile
// void initStack(Stack *s) {
// 	s->top = -1;
// }

// // Empiler un élément sur la pile
// void push(Stack *s, char value) {
// 	s->items[++(s->top)] = value;
// }

// // Dépiler un élément de la pile
// char pop(Stack *s) {
// 	return s->items[(s->top)--];
// }

char	*close_quotes(t_data *data, char *str)
{
	char	closed;
	char	*res;
	char	*line;

	closed = quotes_closed(str);
	if (closed == 0)
		return (str);
	while (closed != 0)
	{
		line = readline("> ");
		if (!line)
		{
			data->ret_val = 2;
			printf("unexpected EOF while looking for matching `%c\"\n", closed);
			return (free(str), NULL);
		}
		res = ft_strjoin(str, line);
		free(str);
		free(line);
		if (!res)
			return (NULL);
		str = res;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:26:21 by fsulvac           #+#    #+#             */
/*   Updated: 2024/06/13 14:45:39 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*init(void)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return NULL;
	tok->str = malloc(sizeof(char));
	if (!(tok->str))
	{
		free(tok);
		return NULL;
	}
	tok->type = STRING; 
	tok->space = true;
	tok->quote = false;
	tok->next = NULL;

	return tok;
}


int len_buffer(char **s)
{
	int i = 0;

	while (s[i] != NULL)
		i++;
	return (i);
}


void split_token(t_token *tok)
{
	char **buff;
	int i;
	t_token *next;
	t_token *new;

	buff = ft_split(tok->str, ' ');
	if (!buff)
	{
		ft_printf_fd(2, "Erreur d'allocation\n");
		return;
	}
	if (len_buffer(buff) == 1)
		return;
	i = 0;
	free(tok->str);
	tok->str = buff[i++];
	tok->space = true;
	next = tok->next;
	while (i < len_buffer(buff))
	{
		new = init();
		if (!new)
		{
			while (buff[i] != NULL)
			{
				free(buff[i]);
				i++;
			}
			free(buff);
			ft_printf_fd(2, "Erreur d'allocation\n");
			return ;
		}
		new->str = buff[i];
		new->type = STRING;
		new->next = next;
		tok->next = new;
		tok = tok->next;
		i++;
	}
	free(buff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:57:37 by fsulvac           #+#    #+#             */
/*   Updated: 2024/06/12 11:57:38 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	tok_del(t_token *tok)
{
	if (tok == NULL)
		return ;
	if (tok->str != NULL)
		free(tok->str);
	free(tok);
}

// Join the two strings
// If the join fails, free memory and return NULL
// Move to the next token

int	token_join_while(t_token *tok)
{
	t_token	*tmp;
	char	*str;

	str = ft_strjoin(tok->str, tok->next->str);
	if (!str)
		return (1);
	free(tok->str);
	tok->str = str;
	if (tok->next->next != NULL && (tok->next->type != OP))
	{
		tmp = tok->next->next;
		tok->space = tok->next->space;
		tok_del(tok->next);
		tok->next = tmp;
	}
	else if ((tok->next != NULL) && (tok->next->next == NULL)
		&& (tok->next->type != OP))
	{
		tok_del(tok->next);
		tok->next = NULL;
	}
	return (SUCCESS);
}

t_token	*token_join(t_token *tok)
{
	t_token	*head;

	head = tok;
	while (tok != NULL)
	{
		while ((tok->next != NULL) && (tok->space == false)
			&& (tok->type != OP) && (tok->next->type != OP))
		{
			if (token_join_while(tok) != SUCCESS)
			{
				free_tok(head);
				ft_printf_fd(2, "Error: allocation");
			}
		}
		tok = tok->next;
	}
	return (head);
}

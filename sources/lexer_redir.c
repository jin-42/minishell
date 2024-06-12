/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:57:54 by fsulvac           #+#    #+#             */
/*   Updated: 2024/06/12 11:57:55 by fsulvac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_double_redir(char *s, int *i, t_token *tok)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		strncpy(tok->str, "<<", 3);
		tok->str[2] = '\0';
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		strncpy(tok->str, ">>", 3);
		tok->str[2] = '\0';
	}
	(*i)++;
}

static void	handle_single_redir(char c, t_token *tok)
{
	tok->str[0] = c;
	tok->str[1] = '\0';
}

t_token	*allocate_token(int i)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * i);
	if (!tok->str)
	{
		free(tok);
		return (NULL);
	}
	return (tok);
}

t_token	*redir(char *s, int *i)
{
	t_token	*tok;

	tok = allocate_token(3);
	if (!tok)
		return (NULL);
	if ((s[*i] == '<' && s[*i + 1] == '<')
		|| (s[*i] == '>' && s[*i + 1] == '>'))
		handle_double_redir(s, i, tok);
	else
		handle_single_redir(s[*i], tok);
	(*i)++;
	tok->type = OP;
	tok->space = false;
	if (s[(*i)] != '\0' && s[(*i)] == ' ')
		tok->space = true;
	tok->quote = false;
	return (tok);
}

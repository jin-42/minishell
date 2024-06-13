/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:58:34 by fsulvac           #+#    #+#             */
/*   Updated: 2024/06/13 13:50:27 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	custom_perror(const char *prefix, const char *filename)
{
	if (prefix)
		fprintf(stderr, "%s", prefix);
	if (filename)
		perror(filename);
	else
		perror(NULL);
}

void	parse_operators(t_data *data, t_token *tok, int i)
{
	t_block	*block;

	block = data->block;
	while (block->next)
		block = block->next;
	if (ft_strncmp(tok->str, ">>", 2) == 0)
	{
		handle_append_redirection(block, tok);
	}
	else if (ft_strncmp(tok->str, "<<", 2) == 0)
	{
		handle_here_document(data, block, tok);
	}
	else if (ft_strncmp(tok->str, ">", 1) == 0)
	{
		handle_output_redirection(block, tok);
	}
	else if (ft_strncmp(tok->str, "<", 1) == 0)
	{
		handle_input_redirection(block, tok);
	}
	else if (ft_strncmp(tok->str, "|", 1) == 0)
	{
		handle_pipe(data, block, tok, i);
	}
}

void	parse_tokens(t_data *data, t_token *co, t_block *head)
{
	int	i;

	i = 0;
	while (co)
	{
		if (co->type == OP || co->type == PIPE)
		{
			parse_operators(data, co, i);
			if (ft_strncmp("|", co->str, 1) == 0)
			{
				i = 0;
				head = head->next;
			}
			else
				co = co->next;
		}
		else
		{
			if (co->str || (co->str && co->str[0] != 0 && co->quote == 0))
				head->args[i++] = ft_strdup(co->str);
		}
		co = co->next;
	}
	if (head->args)
		head->args[i] = NULL;
}

void	parser(t_data *data, t_token *tok)
{
	t_block	*head;
	t_token	*cpy;

	cpy = tok;
	if (cpy == NULL)
		return (error_parser(tok, -1));
	if (!operator_crash(cpy))
		return (error_parser(tok, 1));
	if (init_parser(data) == (-1))
		return (error_parser(tok, 3));
	head = data->block;
	if (head == NULL)
		return (error_parser(tok, 3));
	if (count_av(cpy) != 0)
	{
		head->args = malloc(sizeof(char *) * (count_av(cpy) + 1));
		if (!head->args)
			return (error_parser(tok, 3));
	}
	else
		head->args = NULL;
	parse_tokens(data, cpy, head);
	free_tok(tok);
}

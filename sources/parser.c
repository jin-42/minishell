/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/12 11:58:34 by fsulvac		   #+#	#+#			 */
/*   Updated: 2024/06/17 13:43:53 by sponthus		 ###   ########lyon.fr   */
/*																			*/
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

int	parse_operators(t_data *data, t_token *tok, int i)
{
	t_block	*block;
	int		val;

	val = 0;
	block = data->block;
	while (block->next)
		block = block->next;
	if (ft_strncmp(tok->str, ">>", 2) == 0)
		val = handle_append_redirection(block, tok);
	else if (ft_strncmp(tok->str, "<<", 2) == 0)
	{
		if (handle_here_document(data, block, tok) == 130)
			return (130);
	}
	else if (ft_strncmp(tok->str, ">", 1) == 0)
		val = handle_output_redirection(block, tok);
	else if (ft_strncmp(tok->str, "<", 1) == 0)
		val = handle_input_redirection(block, tok);
	else if (ft_strncmp(tok->str, "|", 1) == 0)
		handle_pipe(data, block, tok, i);
	return (val);
}

int	null_term_args(t_block *head, int i)
{
	if (head->args)
		head->args[i] = NULL;
	return (0);
}

int	parse_tokens(t_data *data, t_token *co, t_block *head)
{
	int	i;
	int	val;

	i = 0;
	while (co)
	{
		if (co->type == OP || co->type == PIPE)
		{
			val = parse_operators(data, co, i);
			if (val != 0)
				return (val);
			if (ft_strncmp("|", co->str, 1) == 0)
			{
				i = 0;
				head = head->next;
			}
			else
				co = co->next;
		}
		else
			if (co->str || (co->str && co->str[0] != 0 && co->quote == 0))
				head->args[i++] = ft_strdup(co->str);
		co = co->next;
	}
	return (null_term_args(head, i));
}

int	parser(t_data *data, t_token *tok)
{
	t_block	*head;
	t_token	*cpy;
	int		val;

	cpy = tok;
	if (cpy == NULL)
		return (error_parser(data, tok, 3));
	if (!operator_crash(cpy))
		return (error_parser(data, tok, 2));
	if (init_parser(data) == 0)
		return (error_parser(data, tok, 3));
	head = data->block;
	if (head == NULL)
		return (error_parser(data, tok, 3));
	if (count_av(cpy) != 0)
	{
		head->args = ft_calloc(count_av(cpy) + 1, sizeof(char *));
		if (!head->args)
			return (error_parser(data, tok, 3));
	}
	else
		head->args = NULL;
	val = parse_tokens(data, cpy, head);
	if (val != 0)
		return (error_parser(data, tok, val));
	return (free_tok(tok), 0);
}

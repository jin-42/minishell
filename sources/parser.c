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
		handle_here_document(block, tok);
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

void	parse_tokens(t_data *data, t_token *copy, t_block *head)
{
	int	i;

	i = 0;
	while (copy)
	{
		if (copy->type == OP)
		{
			parse_operators(data, copy, i);
			if (ft_strncmp("|", copy->str, 1) == 0)
			{
				i = 0;
				head = head->next;
			}
			else
				copy = copy->next;
		}
		else
		{
			if (copy->str && copy->str[0] == '\0' && copy->quote == false) ;
			else if (copy->str)
				head->args[i++] = ft_strdup(copy->str);
		}
		copy = copy->next;
	}
	head->args[i] = NULL;
}

void	error_parser(t_data *data, t_token *tok, int errno)
{
	if (errno > 0)
		free_tok(tok);
	if (errno == 1)
		return ((void)ft_printf_fd(2, "Error: syntax operator\n"));
	else if (errno == 2)
		return ((void)ft_printf_fd(2, "Error: syntaxe backslash\n"));
	else
		return ((void)ft_printf_fd(2, "Error: allocation\n"));
}

void	parser(t_data *data, t_token *tok)
{
	t_block	*head;
	t_token	*cpy;

	cpy = tok;
	if (cpy == NULL)
		return (error_parser(data, tok, -1));
	if (!operator_crash(cpy))
		return (error_parser(data, tok, 1));
	if (last_back_slash(cpy) == true)
		return (error_parser(data, tok, 2));
	if (init_parser(data) == (-1))
		return (error_parser(data, tok, 3));
	head = data->block;
	if (head == NULL)
		return (error_parser(data, tok, 3));
	if (count_av(cpy) != 0)
		head->args = malloc(sizeof(char *) * (count_av(cpy) + 1));
	if (!head->args)
		return (error_parser(data, tok, 3));
	parse_tokens(data, cpy, head);
	free_tok(tok);
}

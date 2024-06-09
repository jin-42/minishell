#include "../includes/minishell.h"

void custom_perror(const char *prefix, const char *filename) {
	if (prefix)
		fprintf(stderr, "%s", prefix);
	if (filename)
		perror(filename);
	else
		perror(NULL);
}

void parse_operators(t_data *data, t_token *tok, int i) 
{
	t_block *block = data->block;

	while (block->next)
		block = block->next;
	if (ft_strncmp(tok->str, ">>", 2) == 0) {
		handle_append_redirection(block, tok);
	} else if (ft_strncmp(tok->str, "<<", 2) == 0) {
		handle_here_document(block, tok);
	} else if (ft_strncmp(tok->str, ">", 1) == 0) {
		handle_output_redirection(block, tok);
	} else if (ft_strncmp(tok->str, "<", 1) == 0) {
		handle_input_redirection(block, tok);
	} else if (ft_strncmp(tok->str, "|", 1) == 0) {
		handle_pipe(data, block, tok, i);
	}
}

void parse_tokens(t_data *data, t_token *copy, t_block *head)
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
			head->args[i++] = ft_strdup(copy->str);
		copy = copy->next;
	}
	head->args[i] = NULL;
}

void parser(t_data *data, t_token *tok)
{
	t_block *head;
	t_token	 *cpy;
	int errno;

	cpy = tok;
	errno = 0;
	if (cpy == NULL)
		return ((void)ft_printf_fd(2, "Error: allocation\n"));
	if (!operator_crash(cpy))
		return (free_tok(tok), (void)ft_printf_fd(2, "Error: syntaxe operator\n"));
	if (last_back_slash(cpy) == true)
		return (free_tok(tok), (void)ft_printf_fd(2, "Error: syntaxe backslash\n"));
	if (init_parser(data) == (-1))
		return (free_tok(tok), (void)ft_printf_fd(2, "Error: allocation\n"));
	head = data->block;
	if (head == NULL)
		return (free(tok), (void)ft_printf_fd(2, "Error: allocation\n"));
	if (count_av(cpy) != 0)
		head->args =  malloc(sizeof(char *) * (count_av(cpy) + 1));
	if (!head->args)
		return (free(tok), ((void)ft_printf_fd(2, "Error: allocation\n")));
	parse_tokens(data, cpy, head);
	free_tok(tok);
}

#include "../includes/minishell.h"

void custom_perror(const char *prefix, const char *filename) {
	if (prefix)
		fprintf(stderr, "%s", prefix);
	if (filename)
		perror(filename);
	else
		perror(NULL);
}

void parse_operators(t_data *data, t_token *tok, int i) {
	t_block *block = data->block;
	while (block->next) {
		block = block->next;
	}
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


// void free_tok(t_token *head)
// {
// 	t_token *current = head;
// 	t_token *temp;

// 	while (current != NULL)
// 	{
// 		if (current->str)
// 			free(current->str);
// 		temp = current;
// 		current = current->next;
// 		free(temp);
// 	}
// }

// void parser(t_data *data, t_token *tok)
// {
//	 t_block *head;
// 	t_block *for_print;
//	 int i = 0;
// 	t_token *copy;

// 	copy = tok;
// 	if (copy == NULL)
// 		return ;
// 	// if (!operator_crash(copy))
// 	// 	return ;
// 	data->block = init_block();
// 	data->cmd_count = data->cmd_count + 1;
// 	head = data->block;
// 	for_print  = data->block;
// 	if (head == NULL)
// 	{
// 		free_tok(tok); // Gestion d'erreur : libérer la mémoire allouée pour les tokens
// 		return ;
// 	}
// 	if (count_av(copy) != 0)
// 		head->args = malloc(sizeof(char *) * (count_av(copy) + 1));
// 	if (!head->args)
// 	{
// 		free_tok(tok);
// 		return ;
// 	}
// 	while (copy)
// 	{
// 		if (copy->type == OP)
// 		{
// 			parse_operators(data, copy, i);
// 			if (ft_strncmp("|", copy->str, 1) == 0)
// 			{
// 				i = 0;
// 				head = head->next;
// 			}
// 		else
// 			copy = copy->next;
// 		}
// 		else

// 			head->args[i++] = ft_strdup(copy->str);
// 		copy = copy->next;
// 	}
// 	head->args[i] = NULL;
// 	print_block(for_print); // a
// 	free_tok(tok);
// }


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

	cpy = tok;
	if (cpy == NULL || !operator_crash(cpy))
		return ;
	if (init_parser(data) == (-1))
		return ;
	head = data->block;
	t_block *for_print = data->block;
	if (head == NULL)
		return (free(tok));
	if (count_av(cpy) != 0)
		head->args =  malloc(sizeof(char *) * (count_av(cpy) + 1));
	if (!head->args)
		return (free(tok));
	parse_tokens(data, cpy, head);
	// print_block(for_print);
	free_tok(tok);
}

#include "../includes/minishell.h"

int	count_av(t_token *head)
{
	t_token	*curr;
	int		i;

	curr = head;
	i = 0;
	while (curr)
	{
		if (ft_strncmp("|", curr->str, 1) == 0 && curr->type == OP)
			break ;
		if (curr->type == OP)
			curr = curr->next;
		else
			i++;
		curr = curr->next;
	}
	return (i);
}

bool	operator_crash(t_token *head)
{
	t_token	*curr;

	curr = head;
	while (curr != NULL)
	{
		if (curr->type == OP && curr->next == NULL)
			return (false);
		else if ((curr->type == OP)
			&& (ft_strncmp(curr->next->str, "<<", 2) != 0)
			&& (curr->next->type == OP))
			return (false);
		curr = curr->next;
	}
	return (true);
}

t_block	*init_block(void)
{
	t_block	*block;

	block = malloc(sizeof (t_block));
	if (!block)
		return (NULL);
	block->in_fd = -2;
	block->out_fd = -2;
	block->here_doc = false;
	block->hd_quote = false;
	block->limiter = NULL;
	block->builtin = false;
	block->path = NULL;
	block->args = NULL;
	block->next = NULL;
	return (block);
}

t_token	*free_tok_go_next(t_token *tok)
{
	t_token	*tmp;

	if (!tok)
		return (NULL);
	tmp = tok->next;
	if (tok->str)
		free(tok->str);
	free(tok);
	return (tmp);
}

int	init_parser(t_data *data)
{
	data->block = init_block();
	if (!data->block)
		return (0);
	data->cmd_count = data->cmd_count + 1;
	return (1);
}

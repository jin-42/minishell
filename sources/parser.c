#include "../includes/minishell.h"

t_block	*init_block()
{
	t_block	*block;

	block = malloc(sizeof (t_block ));
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
	t_token *tmp;

	if (!tok)
		return (NULL);
	tmp = tok->next;
	if (tok->str)
		free(tok->str);
	free(tok);
	return (tmp);
}

void	parse_operators(t_data *data, t_token *tok)
{
	t_block	*block;

	block = data->block;
	while (block)
		block = block->next;
	if (ft_strcmp(tok->str, ">") == 0)
	{
		if (tok->next != 0)
		{
			block->out_fd = open(tok->next->str, O_WRONLY || O_CREAT || O_TRUNC, 0700);
			if (block->out_fd == -1)
			{
				ft_printf_fd(2, "%s: ", tok->next->str);
				perror(NULL);
			}
			tok = free_tok_go_next(tok); // On free le '>'
		}
	}
}

void	parser(t_data *data, t_token *tok)
{
	if (tok == NULL)
		return ;
	data->block = init_block();
	if (data->block == NULL)
		return ; // Gestion erreur a faire , free_tok
	while(tok)
	{
		if (tok->type == OP)
		{
			parse_operators(data, tok);
		}
		tok = free_tok_go_next(tok);
	}
	// while (tok)
	// {
	// 	// Fonction a part qui expand tout ce qui doit l'etre  
	// }
	// Revenir au debut de tok et on gere token / operators
}
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

void	parse_operators(t_data *data, t_token *tok, int i)
{
	t_block	*block;

	block = data->block;
	while (block->next)
		block = block->next;
	if  (ft_strncmp(tok->str, ">>", 2) == 0)
	{
		if (tok->next != 0)
		{
			block->out_fd = open(tok->next->str, O_APPEND, 0700);
			if (block->out_fd == -1)
			{
				ft_printf_fd(2, "%s: ", tok->next->str);
				perror(NULL);
			}
		}
	}
	else if (ft_strncmp((tok->str), "<<", 2) == 0)
	{
		if (tok->next != 0)
		{
			block->here_doc = true;
			if (tok->next->type == STRING_IN_QUOTE)
				block->hd_quote = true;
			block->limiter = ft_strdup(tok->next->str);
			if (block->limiter == NULL)
			{
				ft_printf_fd(2, "%s: ", tok->next->str);
				perror(NULL);
			}
		}
	}
	else if  (ft_strncmp(tok->str, ">", 1) == 0)
	{
		if (tok->next != 0)
		{
			block->out_fd = open(tok->next->str, O_WRONLY || O_CREAT || O_TRUNC, 0700);
			if (block->out_fd == -1)
			{
				ft_printf_fd(2, "%s: ", tok->next->str);
				perror(NULL);
			}
		}
	}
	else if (ft_strncmp(tok->str, "<", 1) == 0)
	{
		if (tok->next != 0)
		{
			block->in_fd = open(tok->next->str, O_RDONLY);
			if (block->in_fd == -1)
			{
				ft_printf_fd(2, "%s: ", tok->next->str);
				perror(NULL);
			}			
		}
	}
	else if (ft_strncmp(tok->str, "|", 1) == 0)
	{
		if (tok->next != 0)
		{
			 t_block *bl;

			 bl = init_block();
			 if (!bl)
				 return ;
			 block->args[i] = '\0';
        		 bl->args = malloc(sizeof(char *) * (count_av(tok->next) + 1));
			 block->next = bl;
		}
	}

}

void print_block(t_block *block) {

while(block != NULL)
{
    printf("in_fd: %d\n", block->in_fd);
    printf("out_fd: %d\n", block->out_fd);
    printf("here_doc: %s\n", block->here_doc ? "true" : "false");
    printf("hd_quote: %s\n", block->hd_quote ? "true" : "false");
    printf("limiter: %s\n", block->limiter != NULL ? block->limiter : "NULL");
	for (int i = 0; block->args[i] != NULL; ++i) {
        printf("agrs[%i] = \t%s\n",i, block->args[i]);
    }
	printf("\n");
	block = block->next;
}
}

void free_tok(t_token *head)
{
	t_token *current = head;
	t_token *temp;

	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

void parser(t_data *data, t_token *tok)
{
    t_block *head;
    int i = 0;

    if (tok == NULL)
        return;
    if (!operator_crash(tok))
        return;
    data->block = init_block();
    head = data->block;
    if (data->block == NULL)
    {
        free_tok(tok); // Gestion d'erreur : libérer la mémoire allouée pour les tokens
        return;
    }
    expander(data, tok);
    if (count_av(tok) != 0)
        data->block->args = malloc(sizeof(char *) * (count_av(tok) + 1));
    if (!data->block->args)
    {
        free_tok(tok);
        return;
    }
    while (tok)
    {
        if (tok->type == OP)
        {
            parse_operators(data, tok, i);
            if (ft_strncmp("|", tok->str, 1) == 0)
            {
                i = 0;
                data->block = data->block->next;
            }
	    else 
		    tok = tok->next;
        }
        else

            data->block->args[i++] = ft_strdup(tok->str);
        tok = tok->next;
    }
    data->block->args[i] = NULL;
    print_block(head);
}

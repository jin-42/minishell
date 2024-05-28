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

char *ft_strdup_var(char *str)
{
	char	*res;
	size_t	len;
	size_t i;

	len = ft_strlen(str);
	res = ft_calloc(len + 2, sizeof (char ));
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	res[i++] = '$'; 
	while (str[len])
	{
		res[i++] = str[len++];
	}
	res[i] = '\0';
	return (res);
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
			if ((tok->next->type == STRING_IN_QUOTE) || tok->next->type == VAR_IN_QUOTE)
				block->hd_quote = true;
			if (tok->next->type == VAR)
				block->limiter = ft_strdup_var(tok->next->str);
			else 
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
			block->out_fd = open(tok->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (block->out_fd == -1)
				perror(custom_error("open: ", tok->next->str));
		}
	}
	else if (ft_strncmp(tok->str, "<", 1) == 0)
	{
		if (tok->next != 0)
		{
			block->in_fd = open(tok->next->str, O_RDONLY);
			printf("opened %s fd is %d\n", tok->next->str, block->in_fd);
			if (block->in_fd == -1)
				perror(custom_error("open: ", tok->next->str));		
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
			data->cmd_count = data->cmd_count + 1;
			block->args[i] = "\0";
        		 bl->args = malloc(sizeof(char *) * (count_av(tok->next) + 1));
			block->next = bl;
		}
	}

}

void free_tok(t_token *head)
{
	t_token *current = head;
	t_token *temp;

	while (current != NULL)
	{
		if (current->str)
			free(current->str);
		temp = current;
		current = current->next;
		free(temp);
	}
}

void parser(t_data *data, t_token *tok)
{
    t_block *head;
    int i = 0;
	t_token *copy;

	copy = tok;
	if (copy == NULL)
		return ;
	if (!operator_crash(copy))
		return ;
	data->block = init_block();
	data->cmd_count = data->cmd_count + 1;
	head = data->block;
	if (head == NULL)
	{
		free_tok(tok); // Gestion d'erreur : libérer la mémoire allouée pour les tokens
		return ;
	}
	expander(data, copy);
	if (count_av(copy) != 0)
		head->args = malloc(sizeof(char *) * (count_av(copy) + 1));
	if (!head->args)
	{
		free_tok(tok);
		return ;
	}
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
	print_block(head);
	free_tok(tok);
}

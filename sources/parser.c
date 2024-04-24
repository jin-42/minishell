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

// void	parse_operators(t_data *data, t_token *tok)
// {
// 	t_block	*block;

// 	block = data->block;
// 	while (block)
// 		block = block->next;
// 	if  (ft_strncmp(tok->str, ">>", 2) == 0)
// 	{
// 		if (tok->next != 0)
// 		{
// 			block->out_fd = open(tok->next->str, O_APPEND/*APPEND*/);
// 			if (block->out_fd == -1)
// 			{
// 				ft_printf_fd(2, "%s: ", tok->next->str);
// 				perror(NULL);
// 			}
// 			tok = free_tok_go_next(tok); // On free le '>'
// 		}
// 	}
// 	else if (ft_strncmp((tok->str), "<<", 2) == 0)
// 	{
// 		if (tok->next != 0)
// 		{
// 			block->here_doc = true;
// 			block->(*limiter) = ft_strdup(tok->next->str);
// 			if (block->(*limiter) == NULL)
// 			{
// 				ft_printf_fd(2, "%s: ", tok->next->str);
// 				perror(NULL);
// 			}
// 			tok = free_tok_go_next(tok);
// 		}
// 	}
// 	else if  (ft_strncmp(tok->str, ">", 1) == 0)
// 	{
// 		if (tok->next != 0)
// 		{
// 			block->out_fd = open(tok->next->str, O_WRONLY || O_CREAT || O_TRUNC, 0700);
// 			if (block->out_fd == -1)
// 			{
// 				ft_printf_fd(2, "%s: ", tok->next->str);
// 				perror(NULL);
// 			}
// 			tok = free_tok_go_next(tok); // On free le '>'
// 		}
// 		else if (ft_strncmp(tok->str, "<", 1) == 0)
// 		{
// 			if (tok->next != 0)
// 			{
// 				block->in_fd = open(tok->next->str, /*droit pour infile*/)
// 				if (block->in_fd == -1)
// 				{
// 					ft_printf_fd(2, "%s: ", tok->next->str);
// 					perror(NULL);
// 				}
// 				tok = free_tok_go_next(tok); // free "<"
// 			}
// 		}
// 	}
// }

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

void utils_expand(t_data *data, t_token *tok)
{

}

// void expand_var_in_quote(t_data *data, t_token *tok)
// {
// 	int i;
// 	int size_expand;
// 	char *tmp;
// 	char	*var;
// 	int		j


// 	i = 0;
// 	while (tok->str[i] != '$')
// 		i++;

// 	size_expand = search_env_size(data, tok->(str + i + 1));
// 	if (size_expand == -1)
// 	{
// 				//expand pas trouve
// 	}
// 	tmp = malloc(sizeof(char) * size_expand + i)
// 	if (!tok->str)
// 		return ; // gestion d'erreur a faire
	
// }

char *ft_strdup_mod(char *s, int start, int end)
{
	char *str;
	int		i;

	str = malloc(sizeof(char) * (end - start +1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

void	parser(t_data *data, t_token *tok)
{
	
	if (tok == NULL)
		return ;
	data->block = init_block();
	if (data->block == NULL)
		return (free_tok(tok)); // Gestion erreur a faire , free_tok
	expand(data, tok);
	// while(tok)
	// {
	// 	if (tok->type == OP)
	// 	{
	// 		parse_operators(data, tok);
	// 	}
	// 	else if (tok->type == STRING)
	// 	{
	// 		args[i++] = strdup((*token)->str);
	// 	}
	// 	tok = free_tok_go_next(tok);
	// }
	// while (tok)
	// {
	// 	if (tok->type == VAR)
	// 	{
	// 		expand = search_env(data, tok->str);
	// 		if (expand == NULL)
	// 		{
	// 			// gestion d'erreur a faire
	// 		}
	// 		free(tok->str);
	// 	}
	// 	char	*search_env(t_data *data, char *name)
	// }
	// 	// Fonction a part qui expand tout ce qui doit l'etre  
	// }
	// Revenir au debut de tok et on gere token / operators

}
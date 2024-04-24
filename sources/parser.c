#include "../includes/minishell.h"

t_block	*init_block()
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
		else if (ft_strncmp(tok->str, "<", 1) == 0) // probleme 
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
}




void print_block(t_block *block) {
    printf("in_fd: %d\n", block->in_fd);
    printf("out_fd: %d\n", block->out_fd);
    printf("here_doc: %s\n", block->here_doc ? "true" : "false");
    printf("hd_quote: %s\n", block->hd_quote ? "true" : "false");
    printf("limiter: %s\n", block->limiter != NULL ? block->limiter : "NULL");
	for (int i = 0; block->args[i] != NULL; ++i) {
        printf("agrs[%i] = \t%s\n",i, block->args[i]);
    }
	printf("next: %p\n", (void *)block->next);
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

int search_env_size(t_data *data, char *name)
{
	t_env	*ptr;
	int		len;

	len = ft_strlen(name);
	ptr = data->env;
	while (ptr != 0)
	{
		if (ft_strncmp(ptr->name, name, len) == 0)
			return ((int)(ft_strlen(ptr->val)));
		ptr = ptr->next;
	}
	return (-1);
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

// void var_in_quote_expand(t_data *data, t_token *tok)
// {
// 	int			i;
// 	int			j;
// 	int			size_expand;
// 	char		*s;
// 	char		*new;

// 	i = 0;
// 	while (tok->str[i] != '$')
// 		i++;
// 	j = i;
// 	while (tok->str[j] != ' ' || tok->str[j] || tok->type != OP)
// 		j++;
// 	s = ft_strdup_mod(tok->str, i + 1, j);
// 	if (!s)
// 		return ;
// 	size_expand = search_env_size(data, s);
// 	// if (size_expand == -1)
// 	// {
// 	// 	//expand
// 	// }
// 	new = ft_substr(tok->str, i, j);
// 	if (j == ft_strlen(tok->str))
// 		tmp = malloc(sizeof(char) * (size_expand + i));
// 	else
// 		tmp = malloc(sizeof(char) * (size_expand + i);
// 	if (!tok->str)
// 		return ;// gestion d'erreir
// }




void expand(t_data *data, t_token *head)
{
	int			size_expand;
	char		*tmp;
	t_token		*tok;

	tok = head;
	while (tok)
	{
		if (tok->type == VAR)
		{
			size_expand = search_env_size(data, tok->str);
			if (size_expand == -1)
				return (free(tok->str));
			tmp = malloc(sizeof(char) * size_expand);
			if (!tok->str)
				return ; // geston d'erreur ?
			ft_strlcpy(tmp, search_env(data, tok->str), size_expand + 1);
			free(tok->str);
			tok->str = tmp;
		}
		tok = tok->next;
	}
}

void	parser(t_data *data, t_token *tok)
{
	int i;
	
	if (tok == NULL)
		return ;
	if (operator_crash(tok) == false)
		return ;
	data->block = init_block();
	i = 0;
	if (data->block == NULL)
		return (free_tok(tok)); // Gestion erreur a faire , free_tok
	expand(data, tok);
	if (count_av(tok) != 0)
		data->block->args = malloc(sizeof(char) + 1);
	if (!data->block->args)
		return ;//Gestion d'erreur
	while (tok)
	{	
		if (tok->type == OP)
		{
			parse_operators(data, tok);
			tok = tok->next;
		}
		else if (tok->type == STRING || tok->type == STRING_IN_QUOTE)
			data->block->args[i++] = ft_strdup(tok->str);
		tok = tok->next;
	}
	data->block->args[i] = '\0';
	print_block(data->block);
}
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
	// Revenir au debut de tok et on gere token / operators//
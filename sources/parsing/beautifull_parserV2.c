#include "../../includes/parsing.h"

int	_find_pipe(t_list *token)
{
	int	count;

	count = 0;
	while (token->next != NULL && strcmp(token->str, "|") != 0)
	{
		token = token->next;
		if (token->type == 2 && token->next != NULL)
		{
			if (token->next->type != 2)
				token = token->next;
		}
		else
			count++;
	}
	return (count);
}

void	free_memory(t_inter *node, int count)
{
	int	j;

	j = 0;
	while (j < count)
	{
		free(node->arr[j++]);
	}
	free(node->arr);
	free(node);
}

void _wich_redir(t_inter **node, t_list **token)
{
    if (strncmp((*token)->str, "<<", 2) == 0)
    {
        if ((*token)->next != NULL && (*token)->next->type != 2)
        {
            memcpy((*node)->heredoc, (*token)->next->str, strlen((*token)->next->str) + 1);
        }
    }
    else if (strncmp((*token)->str, ">>", 2) == 0)
    {
        if ((*token)->next != NULL && (*token)->next->type != 2)
            memcpy((*node)->append, (*token)->next->str, strlen((*token)->next->str) + 1);
    }
    else if (strncmp((*token)->str, "<", 1) == 0)
    {
        if ((*token)->next != NULL && (*token)->next->type != 2)
            memcpy((*node)->infile, (*token)->next->str, strlen((*token)->next->str) + 1);
    }
    else
    {
        if ((*token)->next != NULL && (*token)->next->type != 2)
            *token = (*token)->next;
        memcpy((*node)->outfile, (*token)->next->str, strlen((*token)->next->str) + 1);
    }
}

void	_init_inter(t_inter **node)
{
	(*node)->arr = NULL;
	(*node)->infile = NULL;
	(*node)->outfile = NULL;
	(*node)->heredoc = NULL;
}

void _print_inter(const t_inter *node) {
    if (node == NULL) {
        printf("NULL\n");
        return;
    }

    printf("arr: ");
    if (node->arr != NULL) {
        for (int i = 0; node->arr[i] != NULL; i++) {
            printf("%s ", node->arr[i]);
        }
    }
    printf("\ninfile: %s\noutfile: %s\nheredoc: %s\nappend: %s\n", 
           node->infile ? node->infile : "NULL",
           node->outfile ? node->outfile : "NULL",
           node->heredoc ? node->heredoc : "NULL",
           node->append ? node->append : "NULL");

    printf("next: %p\n", (void *)node->next);
}

t_inter	*_parse(t_list *token)
{
	t_inter	*node;
	int		count;
	int		i;

	node = malloc(sizeof(t_inter));
	if (!node)
		return (NULL);
	_init_inter(&node);
	count = _find_pipe(token);
	node->arr = malloc(sizeof(char *) * (count + 1));
	if (!node->arr)
		return (NULL);
	i = 0;
	printf("a");
	while (token != NULL && strcmp(token->str, "|") != 0)
	{
		node->arr[i] = malloc(sizeof(char) * (strlen(token->str) + 1));
		if (!node->arr[i])
			return (free_memory(node, i), NULL);
		if (token->type != 2)
		{
			strcpy(node->arr[i++], token->str);
		}
		else
			_wich_redir(&node, &token);
		token = token->next;
	}
	node->arr[i] = NULL;
	return (node);
}

# include "../../includes/parsing.h"

int _find_pipe(t_list *token) {
    int count = 0;
    while (token->next != NULL) {
        if (strcmp(token->str, "|") && token->type == 2)
            break;
        else
            count++;
        token = token->next;
    }
    return count;
}

void free_memory(t_inter *node, int count) {
    int j = 0;
    while (j < count) {
        free(node->arr[j++]);
    }
    free(node->arr);
    free(node);
}

void	_wich_redir(t_inter **node, t_list **token)
{
	if (strncmp((*token)->str, "<<", 2) == 0)
	{
		if ((*token)->next->next != NULL && (*token)->next->next->type != 2)
			(*node)->heredoc = strdup((*token)->next->str);
	}
	else if (strncmp((*token)->str, ">>", 2) == 0)
	{
		if ((*token)->next->next != NULL && (*token)->next->next->type != 2)
			(*node)->append = strdup((*token)->next->str);
	}
	else if (strncmp(((*token)->str), "<x", 2))
	{
		if ((*token)->next->next != NULL && (*token)->next->next->type != 2)
			(*node)->infile = strdup((*token)->next->next->str);
	}
	else if (strncmp(((*token)->str), ">x", 2))
	{
		if ((*token)->next->next != NULL && (*token)->next->next->type != 2)
			(*node)->outfile = strdup((*token)->next->str);
	}
	else 
		return ;
}


t_inter *init_inter(void) {
    t_inter *node = malloc(sizeof(t_inter));
    if (!node)
        return NULL;
    node->arr = NULL;
    node->heredoc = NULL;
    node->append = NULL;
    node->outfile = NULL;
    node->infile = NULL;
    node->next = NULL; // Initialisez également next à NULL
    return node;
}

void _print_inter(const t_inter *node) {
    if (node == NULL) {
        printf("Le bloc est vide.\n");
        return;
    }

    // Imprimer les éléments du bloc actuel
    printf("infile: %s\n", node->infile);
    printf("outfile: %s\n", node->outfile);
    printf("append: %s\n", node->append);
    printf("heredoc: %s\n", node->heredoc);

    // Imprimer les éléments du tableau
    if (node->arr != NULL) {
        int i = 0;
        while (node->arr[i] != NULL) {
            printf("arr[%d]: %s\n", i, node->arr[i]);
            i++;
        }
		printf("\n");
    }
    // Appeler la fonction récursivement pour imprimer les blocs suivants
    _print_inter(node->next);
}

t_inter *_parse(t_list **token)
{
    if (!(*token))
        return NULL;
    t_inter *node = init_inter();
    int count = _find_pipe(*token);
    if (!node)
        return NULL;
    node->arr = malloc(sizeof(char *) * (count + 1));
    if (!node->arr) {
        free(node);
        return NULL;
    }
    int i = 0;
    while ((*token)->next != NULL) {
        if (((*token)->type == 2) && strcmp((*token)->str, "|"))
            break;
        _wich_redir(&node, token);
        node->arr[i] = strdup((*token)->str); // Utilisez strdup pour allouer et copier la chaîne
        i++;
        t_list *temp = *token; // Stockez une référence au token actuel
        (*token) = (*token)->next;
        free(temp->str); // Libérez la mémoire pour la chaîne de caractères du token
        free(temp); // Libérez la mémoire pour le token lui-même
    }
    node->arr[i] = NULL;
    return node;
}

t_inter *_parse_add_back(t_list **token) {
    t_inter *head = _parse(token); // Première occurrence
    if (!head)
        return NULL;
    t_inter *current = head;
    while ((*token) && ((*token)->next != NULL)) 
	{ // Vérifiez la non-nullité du token
        t_inter *next_node = _parse(token); // Créer un nouveau nœud
        if (!next_node)
            break;
    	current->next = next_node; // Mettre à jour le pointeur current
        current = next_node;
    	if (((*token)->type == 2) && strcmp((*token)->str, "|") && (*token)->next != NULL)
		{
       		t_list *temp = *token; // Stockez une référence au token actuel
        	(*token) = (*token)->next;
        	free(temp->str); // Libérez la mémoire pour la chaîne de caractères du token
        	free(temp); // Libérez la mémoire pour le token lui-même
		}
    }
    return head; // Retourner le premier élément de la liste chaînée
}


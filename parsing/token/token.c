#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_token
{
	char *str
	t_token next;
} t_token;

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(ptr, newptr, cursize);
	free(ptr);
	return (newptr);
}

void	ft_add_back(t_token **lst, t_token *node)
{
	t_token	*tmp;

	if (!lst || !node)
		return ;
	if (!*lst)
	{
		*lst = node;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

void	ft_skip_space(str, int *i)
{
	while ((str[*i] == ' ')
		(*i)++;
}

t_token *simple_quote(char *str, int *i)
{
    t_token *token = NULL;
    int			j;
	char *temp
    
	j = 0;
    while (str[*i] != '\'' && str[*i] != '\0')
        (*i)++;
    if (str[*i] != '\'')
        return NULL;
    token = malloc(sizeof(t_token));
    if (token == NULL)
        return NULL;
    token->str = malloc(sizeof(char));
    if (token->str == NULL)
        return (free(token), NULL);
    (*i)++;
    while (str[*i] != '\'' && str[*i] != '\0') 
	{
        token->str[j++] = str[(*i)++];
        temp = ft_realloc(token->str, (j + 1) * sizeof(char));
        if (temp == NULL)
           return (free(token->str), free(token), NULL);
        token->str = temp;
    }
    token->str[j] = '\0'; 
    if (str[*i] != '\'') 
        return (free(token->str), free(token), NULL);
    return ((*i)++, token->next = NULL, token);
}


t_token *double_quote(char *str, int *i)
{
    t_token *token = NULL;
    int j = 0;
    
    while (str[*i] != '"' && str[*i] != '\0')
        (*i)++;
    if (str[*i] != '"')
        return NULL;
    token = malloc(sizeof(t_token));
    if (token == NULL)
        return NULL;
    token->str = malloc(sizeof(char));
    if (token->str == NULL)
        return (free(token), NULL);
    (*i)++;
    while (str[*i] != '"' && str[*i] != '\0') 
	{
        token->str[j++] = str[(*i)++];
        token->str = ft_realloc(token->str, (j + 1) * sizeof(char));
        if (token->str == NULL)
			return (free(token->str), free(token), NULL);
    }
    token->str[j] = '\0';   
    if (str[*i] != '"') 
		return (free(token->str), free(token), NULL);
	return ((*i)++, token->next = NULL, token);
}


t_token *no_quote(char *str, int *i)
{
    t_token *token = NULL;
    int j;

	j = 0;
    token = malloc(sizeof(t_token));
    if (token == NULL)
        return (NULL);
    token->str = malloc(sizeof(char));
    if (token->str == NULL)
        return (free(token), NULL);    
    while (str[*i] != '\'' && str[*i] != '\"' && str[*i] != ' ' && str[*i] != '\0') 
	{
        token->str[j++] = str[(*i)++];
        token->str = ft_realloc(token->str, (j + 1) * sizeof(char));
        if (token->str == NULL)
			return (free(token->str), free(token), NULL);
    }
    return (token->str[j] = '\0',token->next = NULL, token);
}



bool count_single_quotes(const char *str) 
{
    int count;

	count = 0;
    while (*str != '\0') {
        if (*str == '\'') {
            count++;
        }
        str++;
    }
    return (count % 2 == 0);
}

bool count_double_quotes(const char *str) 
{
    int count;

	count = 0;
    while (*str != '\0') {
        if (*str == '\"') {
            count++;
        }
        str++;
    }
    return (count % 2 == 0);
}

t_token *lexer(char *s) {
    t_token *node = NULL;
    int i = 0;
    
    if ((count_single_quotes(s) == 0) || (count_double_quotes(s) == 0))
        exit(1);
    ft_skip_space(s, &i);
    while (s[i]) {
        ft_skip_space(s, &i);
        if (s[i] == '\'')
            ft_add_back(&node, simple_quote(s, &i));
        else if (s[i] == '\"')
            ft_add_back(&node, double_quote(s, &i));
        else
            ft_add_back(&node, no_quote(s, &i));
    }
    return node;


int main() {
    char input1[] = "C'est une 'phrase' entre 'guillemets' simples.";
    char input2[] = "C'est une \"phrase\" entre \"guillemets\" doubles.";
    char input3[] = "C'est une phrase sans guillemets.";
    
    // Test de la fonction lexer avec différentes configurations de chaînes
    printf("Test avec la chaîne 1 :\n");
    t_token *tokens1 = lexer(input1);
    t_token *current1 = tokens1;
    while (current1 != NULL) {
        printf("Token : %s\n", current1->str);
        current1 = current1->next;
    }

    printf("\nTest avec la chaîne 2 :\n");
    t_token *tokens2 = lexer(input2);
    t_token *current2 = tokens2;
    while (current2 != NULL) {
        printf("Token : %s\n", current2->str);
        current2 = current2->next;
    }

    printf("\nTest avec la chaîne 3 :\n");
    t_token *tokens3 = lexer(input3);
    t_token *current3 = tokens3;
    while (current3 != NULL) {
        printf("Token : %s\n", current3->str);
        current3 = current3->next;
    }

    // Libération de la mémoire allouée pour les jetons
    // (à implémenter selon vos besoins spécifiques)

    return 0;
}}




# include "minisheel.h"

// Tableau Dynamique

void	*_realloc(void *ptr, size_t newsize)
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

bool _is_full(int num_tokens, int capacity) 
{
	if (num_tokens >= capacity)
		return (true);
	return (false);
}

/*
 *  while ( condition d'ajout de tokens ) {
        // Vérifier si le tableau est plein avant d'ajouter un nouveau token
        if (is_full(num_tokens, capacity)) {
            // Redimensionner le tableau (par exemple, doubler sa capacité)
            capacity *= 2;
            t_lexer_token *temp = realloc(tokens, capacity * sizeof(t_lexer_token));
	    */



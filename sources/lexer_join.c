#include "../includes/minishell.h"

static void tok_del(t_token *tok)
{
    if (tok == NULL)
        return;

    if (tok->str != NULL)
        free(tok->str);

    free(tok);
}

t_token *token_join(t_token *tok)
{
    char *str;
    t_token *tmp;
    t_token *head;

    head = tok;
    while (tok != NULL)
    {
        while ((tok->next != NULL) && (tok->space == false) && (tok->type != OP) && (tok->next->type != OP))
        {
            str = ft_strjoin(tok->str, tok->next->str);  // Join the two strings
            if (!str)
                return (perror("Error:"), free_tok(head), NULL);  // If the join fails, free memory and return NULL
            free(tok->str);
            tok->str = str;
            if (tok->next->next != NULL && (tok->next->type != OP))
            {
                tmp = tok->next->next;  // Save the pointer to the next of the next token
                tok->space = tok->next->space;
                tok_del(tok->next);     // Delete the next token
                tok->next = tmp;        // Update the next pointer to skip the deleted token
            }
            else if ((tok->next != NULL) && (tok->next->next == NULL) && (tok->next->type != OP))
            {
                tok_del(tok->next);
                tok->next = NULL;
            }
        }
        tok = tok->next;  // Move to the next token
    }
    return (head);
}




#include "../includes/minishell.h"


int count_av(t_token *head)
{
    t_token *curr = head;
    int             i;

    i = 0;
    while (curr)
    {
        if (ft_strncmp("|", curr->str, 1) == 0 && curr->type == OP)
            break ;
        if (curr->type == OP)
            curr = curr->next;
        else 
            i++;
        curr = curr->next;
    }
    return (i);
}

bool operator_crash(t_token *head)
{
    t_token *curr = head;

    while (curr != NULL)
    {
        if (curr->type == OP && curr->next == NULL)
            return (false);
        else if ((curr->type == OP) && (ft_strncmp(curr->next->str, "<<", 2) != 0) && (curr->next->type == OP))
            return (false);
        curr = curr->next;
    }
    return (true);
}



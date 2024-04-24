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
        else if (curr->type == OP && curr->next->type == OP)
            return (false);
        curr = curr->next;
    }
    return (true);
}

//do it before lexer
bool quotes_closed(const char* str) 
{
    Stack s;
    initStack(&s);
    int i = 0;
    char c;

    while ((c = str[i++]) != '\0') 
    {
        if (c == '\'' || c == '"') 
        {
            if (s.top == -1 || s.items[s.top] != c) 
            {
                push(&s, c);
            } 
            else
             {
                pop(&s);
            }
        }
    }
    return (s.top == -1);
}

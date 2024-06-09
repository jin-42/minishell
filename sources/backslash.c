#include "../includes/minishell.h"

static int check_last_back_slash(char *s)
{
    int count;
    int i;

    count = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == '\\')
            count++;
        else 
            count = 0;
        i++;
    }
    if (count % 2 == 0)
        return (0);
    return (-1);
}

bool last_back_slash(t_token *tok)
{
    t_token *cpy;

    cpy = tok;
    while (cpy)
    {
        if (check_last_back_slash(cpy->str) == (-1))
            return (true);
        cpy = cpy->next;
    }
    return (false);
}


static void replace_escapes(char *str) 
{
    int len = strlen(str);
    int i = 0;
    while (i < len) 
    {
        if (str[i] == '\\' && i + 1 < len) 
        {
            str[i] = str[i + 1];
            memmove(&str[i + 1], &str[i + 2], len - i - 1);
            str[--len] = '\0';
        }
        i++;
    }
}

void replace_escape(t_token *tok)
{
    t_token *cpy = tok;

    while (cpy)
    {
        if (cpy->quote == false)
            replace_escapes(cpy->str);
        cpy = cpy->next;
    }
}
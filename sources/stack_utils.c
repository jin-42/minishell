#include "../includes/minishell.h"

// Initialisation de la pile
void initStack(Stack *s) {
    s->top = -1;
}

// Empiler un élément sur la pile
void push(Stack *s, char value) {
    s->items[++(s->top)] = value;
}

// Dépiler un élément de la pile
char pop(Stack *s) {
    return s->items[(s->top)--];
}

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
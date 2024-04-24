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
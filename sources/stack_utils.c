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

// bool	quotes_closed(const char* str) 
// {
//	 Stack s;
//	 initStack(&s);
//	 int i = 0;
//	 char c;

//	 while ((c = str[i++]) != '\0') 
//	 {
//		 if (c == '\'' || c == '"') 
//		 {
//			 if (s.top == -1 || s.items[s.top] != c) 
//			 {
//				 push(&s, c);
//			 } 
//			 else
//			  {
//				 pop(&s);
//			 }
//		 }
//	 }
//	 return (s.top == -1);
// }

bool	quotes_closed(const char *str)
{
	int		i;
	bool	res;
	char	c;

	res = true;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			while (str[i])
			{
				if (str[i] == c)
					break ;
				i++;
				if (!str[i])
					res = false;
			}
		}
		if (str[i])
			i++;
	}
	return (res);
}

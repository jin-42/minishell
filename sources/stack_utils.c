#include "../includes/minishell.h"

void	init_stack(Stack *s)
{
	s->top = -1;
}

void	push(Stack *s, char value)
{
	s->items[++(s->top)] = value;
}


char	pop(Stack *s)
{
	return (s->items[(s->top)--]);
}

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

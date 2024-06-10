#include "../includes/minishell.h"

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
			c = str[i++];
			res = false;
			while (str[i])
			{
				if (str[i++] == c)
				{
					res = true;
					break ;
				}
			}
		}
		if (str[i])
			i++;
	}
	return (res);
}

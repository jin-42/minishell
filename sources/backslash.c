/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   backslash.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/12 11:58:53 by fsulvac		   #+#	#+#			 */
/*   Updated: 2024/06/17 14:05:33 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	replace_escapes(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\\' && i + 1 < len)
		{
			str[i] = -str[i + 1];
			ft_memmove(&str[i + 1], &str[i + 2], len - i - 1);
			str[--len] = '\0';
		}
		i++;
	}
}

void	replace_escape(t_token *tok)
{
	t_token	*cpy;

	cpy = tok;
	while (cpy)
	{
		if (cpy->quote == false)
			replace_escapes(cpy->str);
		cpy = cpy->next;
	}
}

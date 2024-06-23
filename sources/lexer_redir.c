/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   lexer_redir.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/12 11:57:54 by fsulvac		   #+#	#+#			 */
/*   Updated: 2024/06/17 13:48:02 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_limiter(t_token *tok)
{
	t_token	*cpy;

	cpy = tok;
	while (cpy)
	{
		if (cpy->type == OP && ft_strncmp(cpy->str, "<<", 2) == 0)
		{
			if (cpy->next != NULL)
				cpy->next->lim = true;
		}
		cpy = cpy->next;
	}
}

static void	handle_double_redir(char *s, int *i, t_token *tok)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		ft_strlcpy(tok->str, "<<", 3);
		tok->str[2] = '\0';
	}
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		ft_strlcpy(tok->str, ">>", 3);
		tok->str[2] = '\0';
	}
	(*i)++;
}

static void	handle_single_redir(char c, t_token *tok)
{
	tok->str[0] = c;
	tok->str[1] = '\0';
}

t_token	*allocate_token(int i)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->str = malloc(sizeof(char) * i);
	if (!tok->str)
	{
		free(tok);
		return (NULL);
	}
	return (tok);
}

t_token	*redir(char *s, int *i)
{
	t_token	*tok;

	tok = allocate_token(3);
	if (!tok)
		return (NULL);
	if ((s[*i] == '<' && s[*i + 1] == '<')
		|| (s[*i] == '>' && s[*i + 1] == '>'))
		handle_double_redir(s, i, tok);
	else
		handle_single_redir(s[*i], tok);
	(*i)++;
	tok->type = OP;
	tok->space = false;
	if (s[(*i)] != '\0' && (s[(*i)] == ' ' || s[(*i)] == '\t'))
		tok->space = true;
	tok->quote = false;
	return (tok);
}

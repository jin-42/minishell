/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   split_token.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/12 13:26:21 by fsulvac		   #+#	#+#			 */
/*   Updated: 2024/06/17 13:31:46 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_allocation_error(char **buff, int i)
{
	while (buff[i] != NULL)
	{
		free(buff[i]);
		i++;
	}
	free(buff);
	ft_printf_fd(2, "Erreur d'allocation\n");
}

static void	handle_split_allocation_error(char **buff)
{
	ft_printf_fd(2, "Erreur d'allocation\n");
	free_full_split(buff);
}

static void	free_and_set_initial_token(t_token *tok, char **buff, int *i)
{
	free(tok->str);
	tok->str = buff[(*i)++];
	tok->space = true;
}

static void	insert_new_tokens(t_token *tok, char **buff, t_token *next, int i)
{
	t_token	*new;

	while (buff[i])
	{
		new = init_split_tok();
		if (!new)
		{
			handle_allocation_error(buff, i);
			return ;
		}
		new->str = buff[i];
		new->next = next;
		tok->next = new;
		tok = tok->next;
		i++;
	}
	free(buff);
}

void	split_token(t_token *tok)
{
	char			**buff;
	int				i;
	t_token			*next;

	buff = ft_split(tok->str, ' ');
	if (!buff)
	{
		handle_split_allocation_error(buff);
		return ;
	}
	if (len_buffer(buff) == 1)
	{
		free_full_split(buff);
		return ;
	}
	i = 0;
	free_and_set_initial_token(tok, buff, &i);
	next = tok->next;
	insert_new_tokens(tok, buff, next, i);
}

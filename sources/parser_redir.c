/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser_redir.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/12 11:59:32 by fsulvac		   #+#	#+#			 */
/*   Updated: 2024/06/17 10:29:23 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_append_redirection(t_block *block, t_token *tok)
{
	int	fd;

	if (tok->next != 0)
	{
		fd = open(tok->next->str, O_APPEND | O_WRONLY | O_CREAT, 0644);
		block->out_fd = fd;
		if (block->out_fd == -1)
		{
			ft_printf_fd(2, "%s: ", tok->next->str);
			perror(NULL);
			return (1);
		}
	}
	return (0);
}

int	handle_here_document(t_data *data, t_block *block, t_token *tok)
{
	if (tok->next != 0)
	{
		if (block->in_fd > 2)
			close(block->in_fd);
		block->here_doc = true;
		if (tok->next->quote == true)
			block->hd_quote = true;
		block->limiter = ft_strdup(tok->next->str);
		if (block->limiter == NULL)
		{
			ft_printf_fd(2, "%s: ", tok->next->str);
			perror(NULL);
			return (1);
		}
		if (heredoc(data, block) == 130)
			return (130);
	}
	return (0);
}

int	handle_output_redirection(t_block *block, t_token *tok)
{
	int	fd;

	if (tok->next != 0)
	{
		if (block->out_fd > 2)
			close(block->out_fd);
		fd = open(tok->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		block->out_fd = fd;
		if (block->out_fd == -1)
		{
			perror(custom_error("open: ", tok->next->str));
			return (1);
		}
	}
	return (0);
}

int	handle_input_redirection(t_block *block, t_token *tok)
{
	char	*str;

	str = NULL;
	if (tok->next != 0)
	{
		if (block->in_fd > 2)
			close(block->in_fd);
		block->here_doc = false;
		block->in_fd = open(tok->next->str, O_RDONLY);
		if (block->in_fd == -1)
		{
			str = custom_error("open: ", tok->next->str);
			perror(str);
			free(str);
			return (1);
		}
	}
	return (0);
}

void	handle_pipe(t_data *data, t_block *block, t_token *tok, int i)
{
	t_block	*bl;

	if (tok->next != 0)
	{
		bl = init_block();
		if (!bl)
			return ;
		data->cmd_count += 1;
		block->args[i] = NULL;
		bl->args = malloc(sizeof(char *) * (count_av(tok->next) + 1));
		if (!bl->args)
			return ;
		block->next = bl;
	}
}

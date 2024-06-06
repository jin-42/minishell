
# include "../includes/minishell.h"

void handle_append_redirection(t_block *block, t_token *tok) 
{
	if (tok->next != 0) {
		block->out_fd = open(tok->next->str, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if (block->out_fd == -1) {
			ft_printf_fd(2, "%s: ", tok->next->str);
			perror(NULL);
		}
	}
}

void handle_here_document(t_block *block, t_token *tok) {
	if (tok->next != 0) {
		block->here_doc = true;
		if (tok->next->quote == true) {
			block->hd_quote = true;
		}
		block->limiter = ft_strdup(tok->next->str);
		if (block->limiter == NULL) {
			ft_printf_fd(2, "%s: ", tok->next->str);
			perror(NULL);
		}
	}
}

void handle_output_redirection(t_block *block, t_token *tok) {
	if (tok->next != 0) {
		block->out_fd = open(tok->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (block->out_fd == -1) {
			perror(custom_error("open: ", tok->next->str));
		}
	}
}

void handle_input_redirection(t_block *block, t_token *tok) 
{
	char	*str;

	str = NULL;
	if (tok->next != 0) {
		block->in_fd = open(tok->next->str, O_RDONLY);
		if (block->in_fd == -1) {
			str = custom_error("open: ", tok->next->str);
			perror(str);
			free(str);
		}
	}
}

void handle_pipe(t_data *data, t_block *block, t_token *tok, int i) {
	if (tok->next != 0) {
		t_block *bl = init_block();
		if (!bl) return;
		data->cmd_count += 1;
		block->args[i] = '\0';
		bl->args = malloc(sizeof(char *) * (count_av(tok->next) + 1));
		block->next = bl;
	}
}
/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/14 14:14:10 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 16:35:23 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../full_libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/ioctl.h>

# define EXP_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789_"
# define SUCCESS 0

extern int	g_signal;

typedef struct s_env
{
	char			*val;
	int				val_len;
	char			*name;
	int				name_len;
	struct s_env	*next;
}	t_env;

typedef struct s_block
{
	int				in_fd; // Open file if < else initialize -2
	int				out_fd; // Open file if > else initialize -2
	bool			here_doc; // True if <<
	bool			hd_quote; // True if limiter contains ' or "
	char			*limiter;
	bool			builtin; // Initialize FALSE
	char			*path; // Initialize to NULL
	char			**args; // 1st = cmd, last = NULL
	struct s_block	*next; // chainer
}	t_block;

typedef struct s_data
{
	t_env	*env;
	char	**environ;
	char	**paths;
	t_block	*block; // 1 par cmd separes par pipes
	int		cmd_count; // Conditionner si < nb de fd
	int		ret_val;
}	t_data;

typedef enum e_bash_op
{
	OP,
	STRING,
	QUOTE,
	PIPE
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	bool			space;
	bool			lim;
	bool			quote;
	struct s_token	*next;
}	t_token;

// Signals
void	signal_init(t_data *data);
void	signals_parent(int signal_code);
void	signals_child(int signal_code);
void	signals_heredoc(int signal_code);
void	signal_exec(void);

// Close quotes
char	quotes_closed(const char *str);
char	*close_quotes(t_data *data, char *str);

// PARSER UTILS
bool	operator_crash(t_token *head);
int		count_av(t_token *head);
void	replace_escape(t_token *tok);

// PARSER UTILS
bool	operator_crash(t_token *head);
int		count_av(t_token *head);
t_block	*init_block(void);
t_token	*free_tok_go_next(t_token *tok);
int		init_parser(t_data *data);

// Parser redir
int		handle_append_redirection(t_block *block, t_token *tok);
int		handle_here_document(t_data *data, t_block *block, t_token *tok);
int		handle_output_redirection(t_block *block, t_token *tok);
int		handle_input_redirection(t_block *block, t_token *tok);
void	handle_pipe(t_data *data, t_block *block, t_token *tok, int i);

// PARSER
int		parser(t_data *data, t_token *tok);

// PARSER - EXPAND
t_token	*init_split_tok(void);
char	*expand_find_name(char *str);
void	expander(t_data *data, t_token *head);
void	split_token(t_token *tok);
int		len_buffer(char **s);

// LEXER
t_token	*lexer(char *s);
void	print_tokens(t_token *tokens);
t_token	*simple_quote(char *s, int *i);
t_token	*double_quote(char *s, int *i);
t_token	*redir(char *s, int *i);
void	free_tok(t_token *head);
int		_lstadd(t_token **lst, t_token *new);
t_token	*token_join(t_token *tok);
char	*ft_strjoin(char const *s1, char const *s2);
int		count_back_slash(char *s);
int		handle_quote(t_token **token, char *s, int *i);
void	check_limiter(t_token *tok);

// ENV PARSING

int		search_env_size(t_data *data, char *name);
t_env	*env_new(char *val, char *name);
int		env_add_back(t_env **env, t_env *new);
int		parse_paths(t_data *data, bool exec);
int		parse_env(t_data *data, char **env);

// ENV MANIP
char	*search_env(t_data *data, char *name);
int		env_size(t_data *data);
char	*env_join(t_env *env, bool exp);
char	**env_to_char(t_data *data, bool exp);
char	**sort_env(t_data *data);

// ENV UTILS

int		parse_empty_env(t_data *data);
void	update_shlvl(t_data *data);
t_env	*search_env_node(t_env *env, char *name);

// EXEC

int		exec(t_data *data);
void	child_process(t_data *data, int i, int *old_pipe, int *new_pipe);
void	parent_process(t_data *data, int pid, int *old_pipe, int *new_pipe);
void	next_block(t_data *data);
void	close_all(t_data *data, int *old_pipe, int *new_pipe);

// EXEC : PATHS
bool	is_a_directory(char *path);
char	**append_cmd(char **paths, char *name);
int		look_in_env(t_data *data, char **paths);
int		search_path(t_data *data);
int		maj_env_paths(t_data *data);

// EXEC : PIPES
void	pipe_manager(int *old_pipe, int *new_pipe);
void	pipe_initializer(int *old_pipe, int *new_pipe);
void	close_pipe(int pipe[2]);

// EXEC : FILES
void	child_infile(t_data *data, int i, int *old_pipe);
void	child_outfile(t_data *data, int i, int *new_pipe);
int		check_files(t_data *data, int i, int *old_pipe, int *new_pipe);
int		check_builtin_files(t_data *data);

// EXEC : HEREDOC

int		heredoc(t_data *data, t_block *block);
int		fill_heredoc(t_data *data, t_block *block, int fd);
char	*expand_heredoc(t_data *data, char *line);
int		error_filling_heredoc(t_data *data, t_block *block, int fd, char *name);

// BUILTIN
int		builtin_process(t_data *data);
int		exec_builtin(t_data *data, char **args, bool ex);
int		cpy_builtin(t_data *data);
bool	is_builtin(t_data *data);

int		pwd(t_data *data, char **args);

int		cd(t_data *data, char **args);
int		maj_pwd(t_data *data, char *old_path);
int		apply_dotdot(t_list **list);
void	free_pwd_args(char **args);
char	*search_cd_path(t_data *data, char *arg);
char	*list_to_char(t_list *list);

int		unset(t_data *data, char **args);
void	env_delone(t_data *data, t_env *node);

int		env(t_data *data, char **args);

int		export(t_data *data, char **args);
int		export_print(t_data *data);
char	*export_find_name(char *arg, char *equal, bool add, bool val);
int		export_arg(t_data *data, char *arg);
int		export_apply(t_data *data, char *name, char *val, bool add);
int		check_var_name(char *name, char *val, char *f);
int		export_replace_val(t_env *node, char *name, char *val, bool add);

int		bt_echo(t_data *data, char **args);
int		count_args(char **args);
bool	echo_is_option(char *arg);

int		bt_exit(t_data *data, char **args, bool print);
int		check_exit_argument(char *arg);
int		contains_digits(char *arg);
int		bt_atoi(char *nptr);

// ERROR
char	*custom_error(char *function, char *arg);
void	error_parsing(t_data *data, char *type);
void	error_exec(t_data *data, int *old_pipe, int *new_pipe, char *str);
void	error_heredoc(t_block *block);
int		error_parser(t_data *data, t_token *tok, int errno);

// FREE
void	free_env_char(t_data *data);
void	leave_minishell(t_data *data, int val);
void	free_env(t_env *env);
void	free_data(t_data *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:14:10 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 13:04:35 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
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

# define EXP_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789_"
# define SUCCESS 0

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
	int				in_fd; // Ouvrir le fichier si < sinon initialiser a -2
	int				out_fd; // Ouvrir le fichier si > sinon initialiser a -2
	bool			here_doc; // Vrai si << alors ce qui suit sera le 1er argument (?)
	bool			builtin; // Initialiser a faux
	char			*path; // Initialiser a NULL
	char			**args; // Tous les args/options de la cmd, 1er = nom de la cmd
	struct s_block	*next; // chainer
}	t_block;

typedef struct s_data
{
	t_env	*env;
	char	**environ;
	char	**paths;
	t_block	*block; // CA, 1 par cmd separes par pipes
	int		cmd_count; // CA
	int		ret_val;
}	t_data;

// enum e_tokens
// {
// 	UNDEFINED,
// 	PIPE,
// 	GREATER
// } ;

// ENV PARSING

t_env	*env_new(char *val, char *name);
int		env_add_back(t_env **env, t_env *new);
int		parse_paths(t_data *data);
int		parse_env(t_data *data, char **env);

// ENV MANIP
char	*search_env(t_data *data, char *name); // Permet de chercher une variable de l'env et rend son contenu.
int		env_size(t_data *data);
char	*env_join(t_env *env, bool exp);
char	**env_to_char(t_data *data, bool exp);
char	**sort_env(t_data *data);

// EXEC

void	exec(t_data *data);
void	child_process(t_data *data, int i, int *old_pipe, int *new_pipe);
void	parent_process(t_data *data, int last_pid, int *old_pipe, int *new_pipe);
void	next_block(t_data *data);
void	close_all(t_data *data, int *old_pipe, int *new_pipe);

// EXEC : PATHS
char	**append_cmd(char **paths, char *name);
int		look_in_env(t_data *data, char **paths);
int		search_path(t_data *data);
int		maj_env_paths(t_data *data);

// EXEC : PIPES
void	pipe_manager(int *old_pipe, int *new_pipe);
void	pipe_initializer(int *old_pipe, int *new_pipe);

// EXEC : FILES
void	child_infile(t_data *data, int i, int *old_pipe, int *new_pipe);
void	child_outfile(t_data *data, int i, int *old_pipe, int *new_pipe);
int		check_files(t_data *data, int i, int *old_pipe, int *new_pipe);

// BUILTIN
int		pwd(t_data *data, char **args);

int		cd(t_data *data, char **args);
int		maj_pwd(t_data *data, char *path, char *old_path);
void	free_pwd_args(char **args);
char	*search_cd_path(t_data *data, char *arg);

int		unset(t_data *data, char **args);
t_env	*search_env_node(t_env *env, char *name);
void	env_delone(t_data *data, t_env *node);

int		env(t_data *data, char **args);

int		export(t_data *data, char **args);
int		print_export(t_data *data);
int		export_arg(t_data *data, char *arg);
int		apply_export(t_data *data, char *name, char *val);
int		check_name(char *name, char *f);

// EXIT
void	free_env(t_env *env);
void	free_data(t_data *data);
void	error_parsing(t_data *data, char *type);
void	error_exec(t_data *data, int *old_pipe, int *new_pipe, char *str);

// test
void	print_data(t_data *data); // A RETIRER

#endif
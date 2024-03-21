/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:14:10 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/21 16:38:36 by sponthus         ###   ########lyon.fr   */
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

# define EXP_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
0123456789_"

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
	int				in_fd;
	int				out_fd;
	bool			here_doc;
	char			*path;
	char			**args;
	struct s_block	*next;
}	t_block;

typedef struct s_data
{
	t_env	*env;
	char	**paths;
	t_block	*block;
	int		cmd_count;
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

// BUILTIN
int		pwd(void);

int		cd(t_data *data, char *path);

int		unset(t_data *data, char *name);
t_env	*search_env_node(t_env *env, char *name);
void	env_delone(t_data *data, t_env *node);

int		env(t_data *data);

int	export(t_data *data, char **arg);
int	print_export(t_data *data);
int	export_arg(t_data *data, char *arg);
char	**sort_env(t_data *data);



// EXIT
void	free_env(t_env *env);
void	free_data(t_data *data);
void	error_parsing(t_data *data, char *type);

// test
void	print_data(t_data *data); // A RETIRER

#endif
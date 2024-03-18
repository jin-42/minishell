/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:14:10 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/18 12:48:00 by sponthus         ###   ########lyon.fr   */
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

typedef struct s_env
{
	char	*val;
	char	*name;
	t_env	*next;
}	t_env;

typedef struct s_block
{
	int		in_fd;
	int		out_fd;
	bool	here_doc;
	char	*path;
	char	**args;
	t_block	*next;
}	t_block;

typedef struct s_data
{
	t_env	*env;
	char	**paths;
	t_block	*block;
	int		cmd_count;
}	t_data;

#endif
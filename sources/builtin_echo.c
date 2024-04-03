/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:53:57 by sponthus          #+#    #+#             */
/*   Updated: 2024/04/03 13:00:53 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Option -n = ne pas afficher le \n final
// prend en compte -nnnn tant que pas d'autre caractere croise, autant que necessaire
// MAIS s'arrete quand on a plus une option, le reste est des args
// Espaces entre les args affiches
// exemple : echo hola -n = pas d'optionm affiche hola -n

bool	echo_is_option(char *arg)
{
	
}

int	echo(t_data *data, char **args)
{
	int	i;
	int	j;

	j = 0;
	while(args && args[j] && echo_is_option(args[i]) == true) // Compter les options
		j++;
	i = j;
	while (args && args[i]) // Compter les args
		i++;
	
}

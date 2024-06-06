/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_echo.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/03 12:53:57 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/06/03 14:37:21 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// Option -n = ne pas afficher le \n final
// prend en compte -nnnn tant que pas d'autre caractere croise, autant que necessaire
// MAIS s'arrete quand on a plus une option, le reste est des args
// Espaces entre les args affiches
// exemple : echo hola -n = pas d'optionm affiche hola -n
// ATTENTION envoyer args + 1
// Check a priori ok

bool	echo_is_option(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i] == 'n')
		i++;
	if (i > 1 && i == ft_strlen(arg))
		return (true);
	return (false);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

int	bt_echo(t_data *data, char **args)
{
	int		i;
	int		j;
	bool	option;

	j = 0;
	(void)data;
	// printf("enter echo");
	option = false;
	while(args && args[j] && echo_is_option(args[j]) == true)
	{
		option = true;
		j++;
	}
	i = count_args(args);
	// printf("i = %d, j = %d\n", i, j);
	while (args && args[j] && j <= i - 1)
	{
		printf("%s", args[j]);
		if (j < i - 1)
			printf(" ");
		j++;
	}
	if (option == false)
		printf("\n");
	return (SUCCESS);
}

// RECTIF A FAIRE Si null ne pas mettre d'espace supplementaire
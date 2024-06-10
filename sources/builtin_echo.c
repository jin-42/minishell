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

// Option -n = do not write final \n
// -nnnnn is an option until another char is recognized
// BUT stops when next arg is not an option anymore, ex -nn hey -nn
// Spaces between args are shown
// ex : echo hola -n = no option shows hola -n
// CAREFUL : seng args + 1
// Check ok

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
	option = false;
	while (args && args[j] && echo_is_option(args[j]) == true)
	{
		option = true;
		j++;
	}
	i = count_args(args);
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

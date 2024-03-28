/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 11:28:47 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/28 17:12:49 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Rend un (int)((i + 256) % 256)
// Realiser un atoi acceptant 1 seul signe
// Sans arg code = 0
// Arguments numeriques code erreur 2 (check en 1er prio sur erreur 1)
// Si plusieurs signes ou lettres : --abc: numeric argument required
// Ne prend que un seul argument sinon trop d'arguments et code erreur 1
// 9223372036854775808 overflow numeric argument required
// -9223372036854775809 underflow idem

int	bt_atoi(char *nptr)
{
	long long	nb;
	int			i;
	int			sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nb != (nb * 10 + ((nptr[i] - '0') * sign)) / 10)
			return (-1);
		nb = (nb * 10) + (nptr[i++] - '0') * sign;
	}
	if (sign == -1)
		return (256 - (((nb * sign) + 256) % 256));
	return ((int)(((nb * sign) + 256) % 256));
}

int	contains_digits(char *arg)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 1)
			val++;
		i++;
	}
	if (val > 0)
		return (1);
	return (0);
}

int	check_exit_argument(char *arg)
{
	int		i;

	i = 0;
	if (contains_digits(arg) == 0 || bt_atoi(arg) < 0)
		return (1);
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[++i])
	{
		if ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == 32)
		{
			while (arg[++i])
			{
				if ((arg[i] < 9 || arg[i] > 13) && arg[i] != 32)
					return (2);
			}
			break ;
		}
		if (arg[i] < '0' || arg[i] > '9')
			return (3);
	}
	return (0);
}

int	bt_exit(t_data *data, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (i == 0)
		{
			if (check_exit_argument(args[i]) != SUCCESS)
			{
				printf("exit: %s: numeric argument required\n", args[i]);
				i = 2;
				break ;
			}
		}
		else if (i == 1)
			return (printf("exit: too many argyments\n"), 1);
		i++;
	}
	if (i != 2)
		i = bt_atoi(args[0]);
	exit(i);
}

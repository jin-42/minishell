/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:58:23 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 15:56:44 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	replace_nb_by_values(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_sign(char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	return (sign);
}

int	ft_base_check(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		if (base[i] == 127 || base[i] <= ' ')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	nb;
	int	baselength;
	int	sign;

	i = 0;
	nb = 0;
	if (ft_base_check(base) == 0)
		return (0);
	baselength = ft_strlen(base);
	sign = ft_sign(str);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (replace_nb_by_values(str[i], base) == -1)
			return (0);
		nb = nb * baselength + replace_nb_by_values(str[i], base);
		i++;
	}
	return (nb * sign);
}

int	ft_atoi(const char *nptr)
{
	long	nb;
	int		i;
	int		sign;

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
			return ((int)((sign + 1) / 2 / -1));
		nb = (nb * 10) + (nptr[i++] - '0') * sign;
	}
	return (nb);
}

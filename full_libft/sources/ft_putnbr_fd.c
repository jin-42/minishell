/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:27:36 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 16:20:43 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		ft_putchar_fd((nb % 10) + '0', fd);
	return ;
}

int	pf_putnbr_fd(long long nb, int wcount, int fd)
{
	int	check1;
	int	check2;

	check1 = 0;
	if (nb < 0)
	{
		check1 = ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb > 9)
	{
		wcount = pf_putnbr_fd(nb / 10, wcount, fd);
		check2 = ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		check2 = ft_putchar_fd((nb % 10) + '0', fd);
	if (check1 == -1 || check2 == -1)
		return (-1);
	wcount = wcount + check1 + check2;
	return (wcount);
}

int	ft_unsigned_putnbr_fd(unsigned long long nb, int wcount, int fd)
{
	int	check;

	if (nb > 9)
	{
		wcount = pf_putnbr_fd(nb / 10, wcount, fd);
		check = ft_putchar_fd((nb % 10) + '0', fd);
	}
	else
		check = ft_putchar_fd((nb % 10) + '0', fd);
	if (check == -1)
		return (-1);
	wcount += check;
	return (wcount);
}
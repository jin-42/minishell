/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:56:36 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 15:56:44 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	number_length(long int n)
{
	size_t	length;

	length = 1;
	if (n < 0)
	{
		n = n * -1;
		length++;
	}
	while (n >= 10)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	nl;

	nl = n;
	len = number_length(nl);
	str = ft_calloc (len + 1, sizeof (char));
	if (!str)
		return (NULL);
	if (nl < 0)
	{
		str[0] = '-';
		nl *= -1;
	}
	if (nl == 0)
		str[0] = '0';
	while (len-- && nl > 0)
	{
		str[len] = (nl % 10) + '0';
		nl = nl / 10;
	}
	return (str);
}

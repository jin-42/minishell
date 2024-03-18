/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:05:24 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 15:56:44 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	srcl;
	size_t	dstl;

	i = 0;
	srcl = 0;
	dstl = 0;
	while (src[srcl])
		srcl++;
	while (dst[dstl] && dstl < size)
		dstl++;
	if (size == 0)
		return (dstl + srcl);
	while (src[i] && i + dstl + 1 < size)
	{
		dst[dstl + i] = src[i];
		i++;
	}
	if (dstl < size)
		dst[dstl + i] = 0;
	return (dstl + srcl);
}

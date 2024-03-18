/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:10:26 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 15:56:44 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	is_charset(char c, char	*charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] && is_charset(s1[i], (char *)set) == 1)
		i++;
	while (s1[i + j])
		j++;
	j--;
	while (is_charset(s1[i + j], (char *)set) == 1 && j >= 0)
		j--;
	j++;
	str = ft_calloc (j + 1, sizeof (char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + i, j + 1);
	return (str);
}

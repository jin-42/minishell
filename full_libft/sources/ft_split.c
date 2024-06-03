/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/13 13:25:09 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/03/11 15:56:44 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

void	free_full_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	if (split[i])
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	free(split);
}

void	free_split(char **str, size_t j)
{
	while (j--)
	{
		free(str[j]);
	}
	free(str);
}

static size_t	count_words(char *str, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (str == NULL)
		return (count);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*next_word(char *str, char c)
{
	char	*word;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = ft_calloc (len + 1, sizeof (char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = ft_calloc (count_words((char *)s, c) + 1, sizeof (char *));
	if (!res)
		return (NULL);
	if (!s)
		return (res);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			res[j++] = next_word((char *)&s[i], c);
			if (!res[j - 1])
				return (free_split(res, j - 1), NULL);
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (res);
}

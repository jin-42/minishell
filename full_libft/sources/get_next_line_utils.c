/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_utils.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/20 16:49:52 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/05/23 15:15:21 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

int	read_file(int fd, char *buf)
{
	int	size;

	size = read(fd, buf, BUFFER_SIZE);
	if (size < 0)
	{
		return (-1);
	}
	buf[size] = '\0';
	return (size);
}

void	*ft_buffmove(char *dest, char *src, size_t size, int *n)
{
	size_t	i;

	i = 0;
	if (*n == 0)
	{
		while (i++ < BUFFER_SIZE + 1)
			*dest++ = '\0';
	}
	else
	{
		while (size-- > 0)
			*dest++ = *src++;
		*dest = '\0';
	}
	return (dest);
}

char	*ft_strlcpy_nl(char *str, char *s, int len, int *n)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (str);
	while (s[i] && s[i] != '\n')
	{
		str[len + i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		str[len + i] = s[i];
		*n = i + 1;
		i++;
	}
	str[len + i] = '\0';
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2, int *n, int size)
{
	char	*str;
	size_t	lens1;

	if (!s1 && !s2)
		return (NULL);
	str = NULL;
	if (s2 == NULL)
		return (s1);
	lens1 = ft_strlen(s1);
	str = malloc(sizeof (char) * (lens1 + size + 1));
	if (str)
	{
		str = ft_strlcpy_nl(str, s1, 0, n);
		str = ft_strlcpy_nl(str, s2, lens1, n);
	}
	if (s1 != NULL)
		free(s1);
	return (str);
}

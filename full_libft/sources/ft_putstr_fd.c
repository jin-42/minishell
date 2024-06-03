/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putstr_fd.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/09 17:31:17 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/03/11 16:19:19 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	res;

	if (s == NULL)
		res = write(fd, "(null)", 6);
	else
		res = write(fd, s, ft_strlen(s));
	return (res);
}

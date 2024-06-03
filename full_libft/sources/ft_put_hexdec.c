/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_put_hexdec.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/21 12:47:32 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/03/11 16:20:18 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_puthexdec_fd(unsigned long long nb, char c, int wcount, int fd)
{
	char	*charset;
	int		check;

	if (c == 'x')
		charset = "0123456789abcdef";
	if (c == 'X')
		charset = "0123456789ABCDEF";
	if (nb >= 16)
	{
		wcount = ft_puthexdec_fd(nb / 16, c, wcount, fd);
		check = ft_putchar_fd(charset[nb % 16], fd);
	}
	else
		check = ft_putchar_fd(charset[nb % 16], fd);
	if (check == -1)
		return (-1);
	wcount += check;
	return (wcount);
}

int	ft_void_puthexdec_fd(void *ptr, int wcount, int fd)
{
	unsigned long long	address;
	int					check;

	check = 0;
	address = (unsigned long long) ptr;
	if (ptr == NULL && wcount == 0)
		check = ft_putstr_fd("(nil)", fd);
	else
	{
		if (wcount == 0)
			check = ft_putstr_fd("0x", fd);
		if (check == -1)
			return (-1);
		wcount += check;
		check = ft_puthexdec_fd(address, 'x', 0, fd);
	}
	if (check == -1)
		return (-1);
	wcount += check;
	return (wcount);
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/21 10:56:53 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/03/11 16:19:49 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

int	charset(char c, char *charset)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_arg(int fd, char c, va_list *arg)
{
	int	wcount;

	wcount = 0;
	if (c == 'c')
		wcount = ft_putchar_fd(va_arg(*arg, int), fd);
	else if (c == 's')
		wcount = ft_putstr_fd(va_arg(*arg, char *), fd);
	else if (c == 'p')
		wcount = ft_void_puthexdec_fd(va_arg(*arg, void *), wcount, fd);
	else if (c == 'd' || c == 'i')
		wcount = pf_putnbr_fd(va_arg(*arg, int), wcount, fd);
	else if (c == 'u')
		wcount = ft_unsigned_putnbr_fd(va_arg(*arg, unsigned int), wcount, fd);
	else if (c == 'x' || c == 'X')
		wcount = ft_puthexdec_fd(va_arg(*arg, unsigned int), c, wcount, fd);
	else if (c == '%')
		wcount = ft_putchar_fd('%', fd);
	else if (c == '\0')
		wcount = -1;
	return (wcount);
}

int	ft_printf_fd(int fd, const char *s, ...)
{
	va_list	arg;
	int		wcount;
	int		tmp;
	int		i;

	if (fd < 0)
		return (-1);
	wcount = 0;
	i = -1;
	va_start(arg, s);
	if (!s)
		return (-1);
	while (s && s[++i])
	{
		if (s[i] != '%' || (s[i] == '%' && charset(s[i + 1], "cspdiuxX%") == 0))
			tmp = ft_putchar_fd(s[i], fd);
		else
			tmp = check_arg(fd, s[++i], &arg);
		if (tmp == -1)
			return (va_end(arg), -1);
		wcount += tmp;
	}
	va_end(arg);
	return (wcount);
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isalnum.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/06 16:27:45 by sponthus		  #+#	#+#			 */
/*   Updated: 2023/11/16 13:58:53 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstclear_bonus.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/14 11:29:37 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/03/11 15:56:44 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;
	t_list	*temp;

	if (lst && del)
	{
		ptr = *lst;
		while (ptr)
		{
			temp = ptr->next;
			(*del)(ptr->content);
			free(ptr);
			ptr = temp;
		}
		*lst = NULL;
	}
	return ;
}

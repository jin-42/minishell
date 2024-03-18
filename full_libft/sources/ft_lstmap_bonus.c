/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sponthus <sponthus@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 11:40:39 by sponthus          #+#    #+#             */
/*   Updated: 2024/03/11 15:56:44 by sponthus         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*tmplst;
	void	*c;

	newlst = NULL;
	while (lst && (*f) && (*del))
	{
		c = (*f)(lst->content);
		if (!c)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		tmplst = ft_lstnew(c);
		if (!tmplst)
		{
			(*del)(c);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, tmplst);
		lst = lst->next;
	}
	return (newlst);
}

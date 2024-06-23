/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   builtin_pwd.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sponthus <sponthus@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/18 13:34:32 by sponthus		  #+#	#+#			 */
/*   Updated: 2024/04/04 16:35:12 by sponthus		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include "../includes/minishell.h"

// Check OK
// arg[0] = pwd

char	*list_to_char(t_list *list)
{
	char	*res;
	char	*tmp;
	t_list	*ptr;

	ptr = list->next;
	if (ptr)
	{
		if (ptr->content)
			res = ft_strjoin("/", (char *)ptr->content);
		ptr = ptr->next;
	}
	while (ptr)
	{
		if (ft_strlen((char *)ptr->content) > 0)
		{
			tmp = ft_strjoin(res, "/");
			free(res);
			res = ft_strjoin(tmp, (char *)ptr->content);
			free(tmp);
		}
		ptr = ptr->next;
	}
	return (res);
}

int	apply_dotdot(t_list **list)
{
	t_list	*prev;
	t_list	*cpy;

	prev = *list;
	cpy = prev->next;
	while (cpy)
	{
		if (cpy->next && ft_strcmp((char *)cpy->next->content, "..") == 0)
		{
			prev->next = cpy->next->next;
			ft_lstdelone(cpy->next, del);
			ft_lstdelone(cpy, del);
			return (1);
		}
		prev = cpy;
		cpy = cpy->next;
	}
	return (0);
}

int	pwd(t_data *data, char **args)
{
	char	*val;
	int		i;

	i = 0;
	(void)data;
	while (args && args[i])
	{
		if (i == 1)
		{
			if (ft_strchr(args[i], '-') != NULL)
				return (printf("pwd: %s: invalid option\n", args[i]), 1);
		}
		i++;
	}
	val = getcwd(NULL, 0);
	if (val == NULL)
	{
		perror("pwd: ");
		return (1);
	}
	printf("%s\n", val);
	free(val);
	return (0);
}

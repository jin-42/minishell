/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsulvac <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:23:42 by fsulvac           #+#    #+#             */
/*   Updated: 2024/03/18 16:56:40 by fsulvac          ###   ########.fr       */
/*                                                                            */

/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char *ft_strtok(char *str, char *ifade) 
{
    static char *item = NULL;
    char *start_item;

    if (str != NULL)
        item = str;
    if (item == NULL || *item == '\0')
        return NULL;
    start_item = item;
    while (*item != '\0') 
    {
        if (strchr(ifade, *item) != NULL) 
	{
            *item = '\0';
            item++;
            break;
        }
        item++;
    }
    return (start_item);
}

int len_tok(char *str)
{
	int i;

	i = 0;
	while (token != NULL) 
	{
        	token = strtok_custom(NULL, delim);
		if (
				i++;
    	}
	return (i);
}

char *ft_tokeniser(char *str)
{
}

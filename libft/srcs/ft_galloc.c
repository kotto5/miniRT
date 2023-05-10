/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_galloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:38:44 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/28 16:22:10 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_galloc(size_t size, t_dlist **alloc_list)
{
	void	*content;
	t_dlist	*new;

	// printf("SIZE = %ld\n", size);
	content = ft_calloc(size, 1);
	if (content == NULL)
		return (NULL);
	new = ft_dlstnew(content);
	if (new == NULL)
	{
		free (content);
		return (NULL);
	}
	ft_dlstadd_back(alloc_list, new);
	return (content);
}

t_list	*ft_lstsearch(t_list *node, void *target)
{
	if (node == NULL || target == NULL)
		return (NULL);
	while (node->next)
	{
		if (node->content == target)
			return (node);
		node = node->next;
	}
	return (NULL);
}

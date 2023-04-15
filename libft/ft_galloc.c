/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_galloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:38:44 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 12:26:18 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_galloc(size_t size, t_dlist **alloc_list)
{
	void	*ptr;

	ptr = calloc(size, 1);
	if (ptr == NULL)
		return (NULL);
	ft_dlstadd_back(alloc_list, ft_dlstnew(ptr));
	return (ptr);
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

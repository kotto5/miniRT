/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsearch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:08:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 12:08:30 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstsearch(t_dlist *node, void *target)
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

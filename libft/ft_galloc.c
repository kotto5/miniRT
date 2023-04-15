/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_galloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:38:44 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 11:05:04 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_galloc(size_t size, t_list **alloc_list)
{
	void	*ptr;

	ptr = calloc(size, 1);
	if (ptr == NULL)
		return (NULL);
	ft_lstadd_back(alloc_list, ft_lstnew(ptr));
	return (ptr);
}

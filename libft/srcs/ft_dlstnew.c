/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:33:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 12:23:26 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//if content is NULL OK

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*ndptr;

	ndptr = malloc(sizeof(t_dlist));
	if (!ndptr)
		return (NULL);
	ndptr -> content = content;
	ndptr -> prev = NULL;
	ndptr -> next = NULL;
	return (ndptr);
}

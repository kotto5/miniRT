/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:33:11 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/15 15:32:55 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//if content is NULL OK

t_dlist	*ft_dlstnew(int content)
{
	t_dlist	*ndptr;

	ndptr = malloc(sizeof(t_dlist));
	if (!ndptr)
		return (NULL);
	ndptr -> content = content;
	ndptr -> times = 0;
	ndptr -> i_done = 0;
	ndptr -> prev = NULL;
	ndptr -> next = NULL;
	return (ndptr);
}

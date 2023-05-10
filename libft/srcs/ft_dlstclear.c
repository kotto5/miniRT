/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:20:14 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/10 15:30:34 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//if there isnt del, its just do free

void	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*ndptr;

	if (lst == NULL)
		return ;
	while (*lst)
	{
		ndptr = (*lst)-> next;
		ft_dlstdelone(*lst, del);
		*lst = ndptr;
	}
	lst = NULL;
}

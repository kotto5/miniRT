/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:02:49 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/27 16:43:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ndptr;

	if (del == NULL || lst == NULL)
		return ;
	while (*lst)
	{
		ndptr = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = ndptr;
	}
	lst = NULL;
}

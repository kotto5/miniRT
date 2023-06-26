/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:20:14 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/05 20:20:24 by shtanemu         ###   ########.fr       */
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
		ndptr = (*lst)->next;
		ft_dlstdelone(*lst, del);
		*lst = ndptr;
	}
	*lst = NULL;
}

// lst = NULL;

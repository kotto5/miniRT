/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:04:54 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/13 14:14:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (lst == NULL || new == NULL)
		return ;
	new -> next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		new -> prev = NULL;
	}
	else
	{
		last = ft_dlstlast(*lst);
		last -> next = new;
		new -> prev = last;
	}
}

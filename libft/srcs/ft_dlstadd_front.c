/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:35:44 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/15 15:26:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	t_dlist	*head;

	if (lst == NULL || new == NULL)
		return ;
	new -> prev = NULL;
	new -> next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		new -> next = NULL;
		new -> prev = NULL;
	}
	else
	{
		head = ft_dlsthead(*lst);
		head -> prev = new;
		new -> next = head;
		*lst = new;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:08:26 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 12:32:59 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// lstnode も content も free する。
// node を消去してprev とnext をつなげる。
// target が先頭のcontent だったら、lst のサスポインタをnextにする

bool	ft_dlstdelete(t_dlist **lst, void *target, void (*del)(void *))
{
	t_dlist	*node;
	t_dlist	*prev;
	t_dlist	*next;

	if (lst == NULL || target == NULL)
		return (false);
	node = ft_dlstsearch(*lst, target);
	if (node == NULL || node->content == NULL)
		return (false);
	prev = node->prev;
	next = node->next;
	ft_dlstdelone(node, del);
	if (prev == NULL)
		*lst = next;
	else
	{
		prev->next = next;
		next->prev = prev;
	}
	return (true);
}

// lstnode 自体はfree しない。
// bool	ft_dlstdelete(t_dlist **lst, void *target, void (*del)(void *))
// {
// 	t_dlist	*node;

// 	if (lst == NULL || target == NULL)
// 		return (false);
// 	node = ft_dlstsearch(*lst, target);
// 	if (node == NULL || node->content == NULL)
// 		return (false);
// 	del(node->content);
// 	node->content = NULL;
// 	return (true);
// }

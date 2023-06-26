/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:08:26 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/05 20:21:07 by shtanemu         ###   ########.fr       */
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
	if (node == NULL)
		return (false);
	prev = node->prev;
	next = node->next;
	if (node == *lst)
		*lst = next;
	ft_dlstdelone(node, del);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:08:26 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/12 17:35:01 by kakiba           ###   ########.fr       */
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


// void	func(void){
	// char		*ptr;
	// static char	*ptr;

	// ptr = malloc(100);
// }

// int	main(void)
// {
// 	char		*ptr;
// 	char		*ptr2;

// 	ptr = malloc(100);
// 	gc_add(ptr);


// 	ptr2 = malloc(100);
// 	gc_add(ptr2);

// 	gc_clear();
// 	// gc_free(ptr2);
// 	// gc_free(ptr2);
// 	// gc_free(ptr);

// 	get_gc_list();
// 	// ptr2 = malloc(100);
// 	// gc_add(ptr2);

// 	// gc_free(ptr2);


// 	// gc_clear();
// 	return (0);
// }


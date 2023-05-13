/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:18:43 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/12 16:46:09 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//del　が無ければlst をフリーするだけ
//del が無い＝構造体はスタック領域のもの

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	t_dlist	*prev;
	t_dlist	*next;

	if (lst == NULL)
		return ;
	prev = lst->prev;
	next = lst->next;
	if (lst->content)
	{
		del(lst->content);
		lst->content = NULL;
	}
	del(lst);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:18:43 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/28 18:38:00 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//del　が無ければlst をフリーするだけ
//del が無い＝構造体はスタック領域のもの

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	if (lst == NULL)
		return ;
	if (lst->content)
	{
		del(lst->content);
		lst->content = NULL;
	}
	del(lst);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:18:43 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/05 20:21:16 by shtanemu         ###   ########.fr       */
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

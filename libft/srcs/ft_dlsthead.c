/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlsthead.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:48:58 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/10 12:02:49 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlsthead(t_dlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst -> prev != NULL)
		lst = lst -> prev;
	return (lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:03:34 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/22 21:33:59 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(double r, double i, void *content)
{
	t_list	*ndptr;

	(void)content;
	ndptr = malloc(sizeof(t_list));
	if (ndptr == NULL)
		return (NULL);
	else
	{
		ndptr -> r = r;
		ndptr -> i = i;
		ndptr -> next = NULL;
		return (ndptr);
	}
}

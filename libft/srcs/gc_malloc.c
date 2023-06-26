/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 20:41:05 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/05 20:41:31 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	**get_gc_list(void)
{
	static t_dlist	*gc;

	return (&gc);
}

void	*gc_malloc(size_t size)
{
	void			*ptr;
	t_dlist			**gc_list;
	t_dlist			*new;

	gc_list = get_gc_list();
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	new = ft_dlstnew(ptr);
	if (new == NULL)
	{
		free (ptr);
		return (NULL);
	}
	ft_dlstadd_front(gc_list, new);
	return (ptr);
}

bool	gc_free(void *ptr)
{
	t_dlist		**gc_list;

	gc_list = get_gc_list();
	return (ft_dlstdelete(gc_list, ptr, free));
}

void	gc_clear(void)
{
	t_dlist		**gc_list;

	gc_list = get_gc_list();
	ft_dlstclear(gc_list, free);
}

// gc_add で同じポインタを二回りストに追加するとdouble free になる（当たり前体操）
bool	gc_add(void *ptr)
{
	t_dlist	**gc_list;
	t_dlist	*node;

	gc_list = get_gc_list();
	node = ft_dlstnew(ptr);
	if (node == NULL)
		return (false);
	ft_dlstadd_front(gc_list, node);
	return (true);
}

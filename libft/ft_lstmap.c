/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:03:20 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/22 21:35:56 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*buf;

	if ((lst == NULL) || (f == NULL))
		return (NULL);
	new_lst = NULL;
	while (lst)
	{	
		buf = ft_lstnew(lst -> i, lst ->r, (f(lst -> content)));
		if (buf == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, buf);
		lst = lst -> next;
	}
	return (new_lst);
}

/*
void	*lstmap_f(void *content) {
	(void)content;
	return ("OK !");
}

int	main()
{
	t_list	*l = ft_lstnew(strdup(" 1 2 3 "));
	t_list	*ret;

	l->next = ft_lstnew(strdup("ss"));
	l->next->next = ft_lstnew(strdup("-_-"));
	ret = ft_lstmap(l, lstmap_f, NULL);
	printf("%p\n", ret);
	printf("%s\n", ret->content);
}*/

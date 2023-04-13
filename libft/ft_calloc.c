/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 23:57:14 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/23 19:50:23 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;

	if (size == 0 || count == 0)
	{
		count = 1;
		size = 1;
	}
	if (count <= __SIZE_MAX__ / size)
	{
		m = malloc(size * count);
		if (m != NULL)
			ft_bzero(m, size * count);
	}
	else
		m = NULL;
	return (m);
}

/*
int	main(void)
{
	int *s1;
	int *s2;
	size_t x = 1234;
	size_t y = 10;

	s1 = ft_calloc(sizeof(int), x);
//	s1 = malloc(sizeof(int) * x);
	printf("calloc()\n");
	for(int i = 0; i < y; ++i)
	{
		printf("%p\n", s1 + i);
		printf("%d\n", s1[i]);
	}
	free (s1);
	// for(int i = 0; i < y; ++i)
	// {
	// 	printf("%d\n", s1[i]);
	// }
	s2 = calloc(sizeof(int), x);
	printf("calloc()\n");
	for(int i = 0; i < y; ++i)
	{
		printf("%p\n", s2 + i);
		printf("%d\n", s2[i]);
	}
	free (s2);
	// for(int i = 0; i < y; ++i)
	// {
	// 	printf("%d\n", s2[i]);
	// }
	return 0;
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:04:32 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/25 22:50:58 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*buf1;
	unsigned char	*buf2;

	if (n == 0)
		return (0);
	buf1 = (unsigned char *)s1;
	buf2 = (unsigned char *)s2;
	i = 0;
	while (i < n && buf1[i] == buf2[i])
		i++;
	if (i == n)
		return (0);
	return (buf1[i] - buf2[i]);
}

/*
int	main()
{
	printf("%d\n", memcmp("ok", "a", 0));
	printf("%d\n", ft_memcmp("ok", "a", 0));
}*/

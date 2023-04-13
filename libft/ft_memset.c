/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:06:20 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/24 19:50:24 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t n)
{
	size_t			i;
	unsigned char	*m;
	unsigned char	c;

	c = (unsigned char)ch;
	m = (unsigned char *)buf;
	i = 0;
	while (i < n)
		m[i++] = c;
	return (m);
}

/*int	main()
{
	void	*s = malloc(2*2);
	printf("%p\n", s);
	printf("%p\n", memset(s, 'a', 1));
	printf("%p\n", ft_memset(s, 'a', 1));
	free(s);
}*/

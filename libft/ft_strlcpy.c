/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:11:20 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/27 14:55:59 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

// int	main()
// {
// 	char s[11];
// 	printf("%ld\n", ft_strlcpy(s, "1234567890", 11));
// 	printf("%s\n", s);
// 	char n[10];
// 	printf("%d\n", strlcpy(n, "abcdefghij", 11));
// 	printf("%s\n", s);
// }

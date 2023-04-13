/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:11:08 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/27 16:26:34 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	while (i < src_len && dest_len + i + 1 < dstsize)
	{
		dst[dest_len + i] = src[i];
		i ++;
	}
	dst[dest_len + i] = '\0';
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	else
		return (dest_len + src_len);
}

//int	main()
// {
// 	char *src1 = malloc(100);
//	src1[0] = 'o';
/*	char *src2 = malloc(100); 
	src2[0] = 'o';
 	printf("%lu\n", strlcat(src1, "h baby", 100));
 	printf("%s\n", src1);
 	printf("%lu\n", ft_strlcat(src2, "h baby", 100));
 	printf("%s\n", src2);
 	
 	printf("%lu\n", strlcat(src1, " un ", ft_strlen(src1) + 3));
 	printf("%s\n", src1);
 	printf("%lu\n", ft_strlcat(src2, " un ", ft_strlen(src2) + 3));
 	printf("%s\n", src2);
 	
 	printf("%lu\n", strlcat(src1, " yeah ", 100));
 	printf("%s\n", src1);
 	printf("%lu\n", ft_strlcat(src2, " yeah ", 100));
 	printf("%s\n", src2);
*/
//	printf("strlcat_%lu\n", strlcat(src1, NULL, 100));
//	printf("strlcat_%lu\n", strlcat(src1, NULL, 0));
//	printf("strlcat_%lu\n", strlcat(src1, NULL, 1));
//	printf("strlcat_%lu\n", strlcat(NULL, src1, 100));
//	printf("strlcat_%lu\n", strlcat(NULL, src1, 0));
//	printf("strlcat_%lu\n", strlcat(NULL, src1, 1));
//	printf("strlcat_%lu\n", strlcat(NULL, NULL, 0));
//	printf("strlcat_%lu\n", strlcat(NULL, NULL, 1));
//	printf("strlcat_%lu\n", strlcat(src1, NULL, ft_strlen(src1) + 3));
//	printf("%s\n", src1);
//	printf("ft______%lu\n", ft_strlcat(src2, NULL, ft_strlen(src2) + 3));
// 	printf("%s\n", src2);

//	printf("strlcat_%lu\n", strlcat(NULL, src1, 0));
//	printf("strlcat_%lu\n", ft_strlcat(NULL, src1, 0));
//	printf("ft______%lu\n", ft_strlcat(NULL, "okey", 5));
//	printf("%s\n", src2); 
//}

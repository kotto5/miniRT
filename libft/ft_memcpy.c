/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:05:52 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/25 22:15:20 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_buf;
	unsigned char	*src_buf;

	i = 0;
	if (src == dest)
		return (dest);
	dest_buf = (unsigned char *)dest;
	src_buf = (unsigned char *)src;
	while (i < n)
	{
		dest_buf[i] = src_buf[i];
		++i;
	}
	return ((void *)dest_buf);
}

//void	*ft_memcpy(void *dest, const void *src, size_t n)
//{
//	return (ft_memmove(dest, src, n));
//}

//
//int	main(void)
//{
//
//	char str3[] = "abcdefghi";
//	char test3[] = "abcdefghi";
//	char test33[] = "abcdefghi";
//	char src [] = "1234567890";
//
//	printf("before_:  %s\n", str3);
//	memmove(test33, src, 6);
//	printf("memmove:  %s\n", test33);
//	memcpy(str3, src, 6);
//	printf("memcpy_:  %s\n", str3);
//	ft_memcpy(test3, src, 6);
//	printf("ft_____:  %s\n\n", test3);
//
////overlap
//	char  str[] = "abcdefghi";
//	char test[] = "abcdefghi";
//	char test00[] = "abcdefghi";
//
////	char * restrict s1 = malloc(100);
////	memmove(s1 + 2, test006);
////	printf("s1: %s\n", s1);
//
//	printf("before_ slide 2 size6:  %s\n", str);
//	memmove(test00 + 2, test00, 6);
//	printf("memmove:  %s\n", test00);
//	memcpy(str + 2, str, 6);
//	printf("memcpy_:  %s\n", str);
//	ft_memcpy(test + 2, test, 6);
//	printf("ft_____:  %s\n\n", test);
//
//	char str2[] = "abcdefghi";
//	char test2[] = "abcdefghi";
//	char test22[] = "abcdefghi";
//
//	printf("before_:  %s\n", str2);
//	memmove(test22, test22 + 3, 6);
//	printf("memmove:  %s\n", test22);
//	memcpy(str2, str2 + 3, 6);
//	printf("memcpy_:  %s\n", str2);
//	ft_memcpy(test2, test2 + 3, 6);
//	printf("ft_____:  %s\n\n", test2);
//
//	// printf("error_check: %s\n", (char *)memcpy(str, NULL, 1));
//	// printf("error_check: %s\n", (char *)ft_memcpy(str, NULL, 1));
//	//printf("error_check: %s\n", (char *)memcpy(NULL, str, 1));
//	// printf("error_check: %s\n", (char *)ft_memcpy(NULL, str, 1));
//	// printf("error_check: %s\n", (char *)memcpy(NULL, NULL, 1));
//	// printf("error_check: %s\n", (char *)ft_memcpy(NULL, NULL, 1));
//
//return 0;
//}
//

// int main(void)
// {
// 	int	i;
// 	char str[5];

// 	i = 0;
// 	ft_memcpy(str, "okey", 5);

// 	while(i < 5)
// 	{
// 		write (1, str + i, 1);
// 		i++;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:06:08 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/25 22:15:42 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src)
		return (dest);
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = 1;
		while (i <= n)
		{
			*(unsigned char *)(dest + n - i) = *(unsigned char *)(src + n - i);
			i++;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char str3[] = "abcdefghijklmnopqrstu";
// 	char test3[] = "abcdefghijklmnopqrstu";
// 	char src [] = "1234567890";

// 	printf("before: %s\n", str3);
// 	memmove(str3, src, 10);
// 	printf("after:  %s\n", str3);
// 	ft_memmove(test3, src, 10);
// 	printf("after:  %s\n\n", test3);

// 	char str[] = "abcdefghijklmnopqrstu";
// 	char test[] = "abcdefghijklmnopqrstu";

// 	printf("before: %s\n", str);
// 	memmove(str + 5, str, 10);
// 	printf("after:  %s\n", str);
// 	ft_memmove(test + 5, test, 10);
// 	printf("after:  %s\n\n", test);

// 	char str2[] = "abcdefghijklmnopqrstu";
// 	char test2[] = "abcdefghijklmnopqrstu";

// 	printf("before: %s\n", str2);
// 	memmove(str2, str2 + 5, 10);
// 	printf("after:  %s\n", str2);
// 	ft_memmove(test2, test2 + 5, 10);
// 	printf("after:  %s\n\n", test2);

	// printf("error_check: %s\n", (char *)memmove(str, NULL, 1));
	// printf("error_check: %s\n", (char *)ft_memmove(str, NULL, 1));
	// printf("error_check: %s\n", (char *)memmove(NULL, str, 1));
	// printf("error_check: %s\n", (char *)ft_memmove(NULL, str, 1));
	// printf("error_check: %s\n", (char *)memmove(NULL, NULL, 1));
	// printf("error_check: %s\n", (char *)ft_memmove(NULL, NULL, 1));

// return 0;
// }

// int	main()
// {
// 	char	array[] = "akiba";
// 	char	*ptr = "hello";

// 	printf("array:%s\n", array);
// 	printf("array ptr:%p\n", &array);
// 	printf("array ptr:%p\n", array);
// 	for (int i = 0; array[i]; ++i)
// 	{
// 		printf("array:%d, %p   ", i,  &array[i]);
// 		printf("array:%d, %p   ", i,  &array + i);
// 	}
// 	printf("\n");
// 	printf("ptr:%s\n", ptr);
// 	printf("ptr ptr:%p\n", ptr);
// 	printf("ptr ptr:%p\n", &ptr);
// 	for (int i = 0; ptr[i]; ++i)
// 	{
// 		printf("ptr:%d, %p   ", i,  &ptr[i]);
// 		printf("ptr:%d, %p   ", i,  (&ptr + i));
// 	}
// 	printf("\n");
// }
// // the differense between array and pointer is that 
// // the variable of array is directly store
// // elements (find out G66), whereas pointer point 
// // by a pointer and can be navigated using pointer.

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:11:53 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/24 21:44:01 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	if (needle[0] == '\0')
		return ((char *)(haystack));
	if (len == 0)
		return (NULL);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i + needle_len <= len
		&& ft_strncmp(&haystack[i], needle, needle_len))
		i++;
	if (i + needle_len > len || !(haystack[i]))
		return (NULL);
	else
		return ((char *)haystack + i);
}
/*
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				j++;
				if (j == ft_strlen(needle))
					return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
	*/
/*
int	main()
{
//normal
	printf("%p\n", strnstr("abcd", "ab", 1));
	printf("%p\n", ft_strnstr("abcd", "ab", 1));
//normal
	printf("%p\n", strnstr("a", "a", 1));
	printf("%p\n", ft_strnstr("a", "a", 1));
//normal
	printf("%p\n", strnstr("abc", "bc", 2));
	printf("%p\n", ft_strnstr("abc", "bc", 2));
//normal
	printf("%p\n", strnstr("abc", "bc", 3));
	printf("%p\n", ft_strnstr("abc", "bc", 3));
//needle = NULL
//	printf("%s\n", strnstr("abcde", NULL, 3));
//	printf("%s\n", ft_strnstr("abcde", NULL, 3));
//needle = ""
	printf("kore%p\n", strnstr("abcde", "", 3));
	printf("%p\n", ft_strnstr("abcde", "", 3));
//lack lenghts
	printf("%p\n", strnstr("abcde", "bc", 2));
	printf("%p\n", ft_strnstr("abcde", "bc", 2));
//len = 0
	printf("%p\n", strnstr("abcde", "bc", 0));
	printf("%p\n", ft_strnstr("abcde", "bc", 0));
//hay = NULL && len != 0 SGF 
//	printf("%s\n", strnstr(NULL, "bc", 2));
//	printf("%s\n", ft_strnstr(NULL, "bc", 2));
//hay = NULL && len = 0 NULL
	printf("%p\n", strnstr(NULL, "bc", 0));
	printf("%p\n", ft_strnstr(NULL, "bc", 0));
//hay = NULL && len = 0 && needle == NULL  SGF
//	printf("%s\n", strnstr(NULL, NULL, 0));
//	printf("%s\n", ft_strnstr(NULL, NULL, 0)); 
	return (0);
}*/

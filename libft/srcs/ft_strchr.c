/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:07:37 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/24 15:48:07 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}
/*
int	main()
{
	char	*s = "abcdefg";
	//ordinary
	printf("org_:%s\n", strchr(s, 'c'));
	printf("ft__:%s\n", ft_strchr(s, 'c'));
	//NULL
	printf("org_:%s\n", strchr(s, '\0'));
	printf("ft__:%s\n", ft_strchr(s, '\0'));
	//nothing
	printf("org_:%s\n", strchr(s, 'A'));
	printf("ft__:%s\n", ft_strchr(s, 'A'));
}*/

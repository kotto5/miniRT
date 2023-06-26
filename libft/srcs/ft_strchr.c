/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:07:37 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/22 16:24:31 by shtanemu         ###   ########.fr       */
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

char	*ft_strchr_s(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	return (ft_strchr(s, c));
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

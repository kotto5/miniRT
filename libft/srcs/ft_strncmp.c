/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:11:43 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/25 19:07:57 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	if ((s1[i] == '\0' || s2[i] == '\0') && i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

int	ft_strcmp_s(const char *s1, const char *s2)
{
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	if ((s1[i] == '\0' || s2[i] == '\0'))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
int	main()
{
	printf("%d", ft_strncmp(NULL, "ok", 0));
	printf("%d", strncmp(NULL, "ok", 0));
//	printf("%d", strncmp("ok", NULL, 3));
	return (0);
}
*/

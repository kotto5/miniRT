/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:08:40 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/27 15:58:42 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char const *s1);

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	src_len;

	src_len = ft_strlen(s1);
	dest = malloc(sizeof(char) * (src_len + 1));
	if (dest == NULL)
		return (NULL);
	ft_strcpy(dest, s1);
	return (dest);
}

static char	*ft_strcpy(char *dest, char const *s1)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}

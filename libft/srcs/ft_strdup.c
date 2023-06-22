/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:08:40 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/22 15:59:58 by shtanemu         ###   ########.fr       */
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

char	*ft_strdup_s(const char *s1)
{
	if (s1 == NULL)
		return (NULL);
	return (ft_strdup(s1));
}

char	*ft_strndup_s(const char *str, size_t len)
{
	char	*dupped_str;
	size_t	i_str;

	if (str == NULL)
		return (NULL);
	dupped_str = (char *)malloc(sizeof(char) * (len + 1));
	if (dupped_str == NULL)
		return (NULL);
	i_str = 0;
	while (str[i_str] != '\0' && i_str < len)
	{
		dupped_str[i_str] = str[i_str];
		i_str++;
	}
	dupped_str[i_str] = '\0';
	return (dupped_str);
}
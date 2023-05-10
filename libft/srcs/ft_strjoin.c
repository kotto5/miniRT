/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:10:04 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/27 08:07:49 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = (char *)malloc(len1 + len2 + 1);
	if (s3 == NULL)
		return (NULL);
	ft_memmove(s3, s1, len1 + 1);
	ft_memmove(s3 + ft_strlen(s3), s2, len2 + 1);
	return (s3);
}
//if there is not 1, occurs error as if there are
//some data that isn't 0 after s3 end,
// //What make the difference when I use sizeof() and ft_strlen()?
//this line's ft_strlen() have more nomber than s1.

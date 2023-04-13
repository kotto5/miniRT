/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:12:30 by kakiba            #+#    #+#             */
/*   Updated: 2022/08/03 17:16:59 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	char	*s2;

	i = 0;
	if (set == NULL || s1 == NULL)
		return (NULL);
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	if (s1[i] == '\0')
		return (ft_calloc(0, 0));
	start = i;
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i)
		i--;
	s2 = ft_substr(s1, start, i - start + 1);
	return (s2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:12:30 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/25 19:08:24 by shtanemu         ###   ########.fr       */
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

char	*ft_strtrim_free_s1(char *s1, char const *set)
{
	char	*trimed_str;

	trimed_str = ft_strtrim(s1, set);
	free(s1);
	return (trimed_str);
}

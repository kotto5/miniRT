/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 20:25:36 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/10 18:01:20 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// if remain has nothing, strchr() overflow so it must have length.
// Name is easily confused original strchr...

char	*ft_gn_strchr(const char *s, int c, size_t length)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < length && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

// to clear remain, fill src '\0'
size_t	ft_gn_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		++i;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	while (src[i] != '\0' && i < dstsize)
		i++;
	return (i);
}

//after read, to stop Line112
//newsizw = 0 notoki
//realloc de kanketu 
//error notokimo free suru?
//error early return 
//for ha strlcpy
void	*ft_gn_realloc(void *src, size_t src_size, size_t new_size)
{
	void	*dst;

	dst = malloc(new_size);
	if (src_size != 0 && dst)
	{
		if (src_size < new_size)
			ft_gn_strlcpy((char *)dst, (char *)src, src_size);
		else
			ft_gn_strlcpy((char *)dst, (char *)src, new_size);
	}
	free (src);
	src = NULL;
	return (dst);
}

void	*ft_gn_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*m;

	m = (unsigned char *)s;
	i = 0;
	while (i < n)
		m[i++] = '\0';
	return (m);
}

int	invalid_check(char *buf, int fd)
{
	if (buf == NULL)
		return (1);
	if (fd == -1)
	{
		free (buf);
		return (1);
	}
	return (0);
}

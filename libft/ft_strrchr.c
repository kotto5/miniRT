/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:12:22 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/24 21:34:00 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s);
	ptr = (char *)s;
	while (len >= i)
	{
		if (ptr[len - i] == (char)c)
			return (&ptr[len - i]);
		i++;
	}
	return (NULL);
}

//
//int	main()
//{
//	printf("%s\n", strrchr("abc", 'b' + 256));
//	printf("%s\n", ft_strrchr("abc", 'b' + 256));
//}

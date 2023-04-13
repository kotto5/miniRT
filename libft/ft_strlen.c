/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 00:11:27 by kakiba            #+#    #+#             */
/*   Updated: 2022/07/22 06:33:30 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// size_t	ft_s_strlen(const char *str)
// {
// 	if (str == NULL)
// 		return (0);
// 	else
// 		return (ft_strlen(str));
// }

// int	main(void)
// {
// 	char	*s = NULL;

// 	printf("%ld\n", strlen("0123456789"));
// 	printf("%ld\n", ft_strlen("0123456789"));
// 	printf("%ld\n", strlen("o\0k"));
// 	printf("%ld\n", ft_strlen("o\0k"));
// 	printf("%ld\n", strlen(""));
// 	printf("%ld\n", ft_strlen(""));
// 	printf("%ld\n", strlen(s));
// 	printf("%ld\n", ft_strlen(s));
// 	return (0);
// }

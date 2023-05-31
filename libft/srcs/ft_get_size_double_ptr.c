/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_size_double_ptr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:26:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/31 17:17:38 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	get_size_double_ptr(char **ptr)
{
	size_t	len;

	len = 0;
	if (!ptr)
		return (0);
	while (ptr[len])
		len++;
	return (len);
}

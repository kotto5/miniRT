/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:02:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/01/19 11:28:01 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 1	OK
// 01	ERROR
// -1	OK
// +1	OK
// --1	ERROR
// -1-	ERROR

static	size_t	get_nums_of_sign(char *str, size_t len);

int	ft_isdigit_str(char *str, size_t sign_allowable)
{
	size_t	i;
	size_t	len;
	size_t	nums_of_sign;
	char	start_of_digit;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	i = 0;
	nums_of_sign = get_nums_of_sign(str, len);
	if (nums_of_sign > sign_allowable)
		return (0);
	i += nums_of_sign;
	start_of_digit = str[i];
	if (start_of_digit == '0')
		return (0);
	while (i < len)
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

static	size_t	get_nums_of_sign(char *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && (str[i] == '+' || str[i] == '-'))
		++i;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:31:23 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/05 20:42:39 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nums_of_sign(char *str);
static int		isvalid_double_point(char *str, size_t len);
static bool		check_digit(char *str);

int	ft_isdouble(char *str)
{
	size_t	i;
	size_t	len;

	if (str == NULL)
		return (0);
	len = ft_strlen(str);
	i = get_nums_of_sign(str);
	if (len - i == 0 || i >= 2 || !isvalid_double_point(str, len))
		return (0);
	if (str[i] == '0')
		if (str[i + 1] != '.' && str[i + 1] != '\0')
			return (0);
	while (i < len)
	{
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (0);
		i++;
	}
	if (!check_digit(str))
		return (0);
	return (1);
}

static	size_t	get_nums_of_sign(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && (str[i] == '+' || str[i] == '-'))
		++i;
	return (i);
}

static	int	isvalid_double_point(char *str, size_t len)
{
	size_t	i;
	size_t	count_double;

	i = 0;
	while (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '.' || str[len - 1] == '.')
		return (0);
	count_double = 0;
	while (i < len && count_double <= 1)
	{
		if (str[i] == '.')
			++count_double;
		++i;
	}
	if (count_double >= 2)
		return (0);
	else
		return (1);
}

static bool	check_digit(char *str)
{
	size_t	i;
	size_t	digit;

	i = get_nums_of_sign(str);
	digit = 1;
	while (ft_isdigit(str[i]))
	{
		++i;
		digit++;
	}
	if (digit > 11)
		return (0);
	digit = 1;
	if (str[i] == '.')
		++i;
	while (ft_isdigit(str[i]))
	{
		++i;
		digit++;
	}
	if (digit > 6)
		return (0);
	++i;
	return (1);
}

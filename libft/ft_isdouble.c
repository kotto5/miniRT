/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:31:23 by kakiba            #+#    #+#             */
/*   Updated: 2023/02/09 15:15:04 by kakiba           ###   ########.fr       */
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
	if (len != 1 && str[len - 1] == '0')
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

// int	ft_isdouble(char *str)
// {
// 	size_t	i;
// 	size_t	len;

// 	if (str == NULL)
// 		return (0);
// 	len = ft_strlen(str);
// 	i = get_nums_of_sign(str);
// 	if (len - i == 0 || i >= 2 || !isvalid_double_point(str, len))
// 	{
// 		// if (len - i == 0)
// 		// ;	// printf("test1: only sign\n");
// 		// else if (i >= 2)
// 		// ;	// printf("test2: many sign\n");
// 		// else if (!isvalid_double_point(str, len))
// 		// ;
// 		// 	// printf("test3: invalid point\n");
// 		return (0);
// 	}
// 	if (str[i] == '0')
// 	{
// 		if (str[i + 1] != '.' && str[i + 1] != '\0')
// 		{
// 			// printf("test4: 0 start but not 0 or double\n");
// 			return (0);
// 		}
// 	}
// 	if (len != 1 && str[len - 1] == '0')
// 	{
// 		// printf("test8: ended zero\n");
// 		return (0);
// 	}
// 	while (i < len)
// 	{
// 		if (!ft_isdigit(str[i]) && str[i] != '.')
// 		{
// 			// printf("test5: there is not digit or point\n");
// 			return (0);
// 		}
// 		i++;
// 	}

// 	if (!check_digit(str))
// 		return (0);
// 	return (1);
// }

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

// static bool	check_digit(char *str)
// {
// 	size_t i;
// 	size_t digit;

// 	i = get_nums_of_sign(str);
// 	digit = 1;
// 	while (ft_isdigit(str[i]))
// 	{
// 		++i;
// 		digit++;
// 	}
// 	if (digit > 11)
// 	{
// 		printf("test6 : too many num over point\n");
// 		return (0);
// 	}
// 	digit = 1;
// 	if (str[i] == '.')
// 		++i;
// 	while (ft_isdigit(str[i]))
// 	{
// 		++i;
// 		digit++;
// 	}
// 	if (digit > 6)
// 	{
// 		printf("test7 : too many num under point\n");
// 		return (0);
// 	}
// 		++i;
// 	return (1);
// }

// int	main(void)
// {
// 	//OK
// 	printf("OK\n");
// 	printf("0: %d\n", ft_isdouble("0"));
// 	printf("12345: %d\n", ft_isdouble("12345"));
// 	printf("24893: %d\n", ft_isdouble("24893"));
// 	printf("0.31247: %d\n", ft_isdouble("0.31247"));
// 	//NO
// 	printf("NO\n");
// 	printf("-0: %d\n", ft_isdouble("-0"));
// 	printf("+0: %d\n", ft_isdouble("+0"));
// 	printf("01:  %d\n", ft_isdouble("01"));
// 	printf("empty str:  %d\n", ft_isdouble(""));
// 	printf("--:  %d\n", ft_isdouble("--"));
// 	printf("++:  %d\n", ft_isdouble("++"));
// 	printf("+: %d\n", ft_isdouble("+"));
// 	printf("-: %d\n", ft_isdouble("-"));
// 	printf("+00: %d\n", ft_isdouble("+00"));
// 	printf("-00: %d\n", ft_isdouble("-00"));
// 	printf("0.0: %d\n", ft_isdouble("0.0"));
// 	printf("0.000: %d\n", ft_isdouble("0.0"));
// 	printf("a: %d\n", ft_isdouble("a"));
// 	printf("0.a: %d\n", ft_isdouble("0.a"));
// 	printf("0a.1: %d\n", ft_isdouble("0a.1"));
// 	printf("a.2: %d\n", ft_isdouble("a.2"));
// 	printf("12345.: %d\n", ft_isdouble("12345."));
// 	printf("12345..: %d\n", ft_isdouble("12345.."));
// 	printf(".12345: %d\n", ft_isdouble(".12345"));
// 	printf("..12345: %d\n", ft_isdouble("..12345"));
// 	printf(".1: %d\n", ft_isdouble(".1"));
// 	printf("..1: %d\n", ft_isdouble(".1"));
// 	printf("...1: %d\n", ft_isdouble(".1"));
// 	printf("0.931824782795: %d\n", ft_isdouble("0.931824782795"));
// 	printf("1234567890123456.9843771289: %d\n", ft_isdouble("1234567890123456.9843771289"));
// }


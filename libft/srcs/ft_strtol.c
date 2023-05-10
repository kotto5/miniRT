/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:06:13 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/16 17:08:48 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_check(const char *nptr, int *base, int *judge_minus);
static int	index_check(char c, int base);

long int	ft_strtol(const char *nptr, char **endptr, int base)
{
	size_t				i;
	int					judge_minus;
	unsigned int long	sum;

	sum = 0;
	judge_minus = 1;
	i = start_check(nptr, &base, &judge_minus);
	while (index_check(nptr[i], base) != -1)
	{
		if ((sum <= (unsigned int long)
				(LONG_MAX - index_check(nptr[i], base)) / base))
			sum = sum * base + index_check(nptr[i++], base);
		else if (judge_minus == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	if (endptr != NULL)
		*endptr = (char *)&nptr[i];
	return (judge_minus * sum);
}

static int	start_check(const char *nptr, int *base, int *judge_minus)
{
	size_t	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		*judge_minus = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if ((*base == 0 || *base == 16) && nptr[i] == '0'
		&& (nptr[i + 1] == ('x') || nptr[i + 1] == ('X')))
	{
		i = i + 2;
		*base = 16;
	}
	else if ((*base == 0 || *base == 8) && nptr[i] == '0')
	{
		i++;
		*base = 8;
	}
	return (i);
}

static int	index_check(char c, int base)
{
	if (ft_isalnum(c) && '0' + base > c)
		return (c - '0');
	else if (ft_isalpha(ft_toupper(c)) && base > 10 && 'A' + base - 10 > c)
		return (c - 'A' + 11);
	else
		return (-1);
}

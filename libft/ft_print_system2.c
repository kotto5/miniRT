/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_system2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:50:31 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/04 14:37:05 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_puthex_fd(unsigned long long n, int fd, char c)
// {
// 	int			written;

// 	written = 0;
// 	// if (n == LLONG_MIN)
// 	// 	return (write (1, "80000000", 8));
// 	// else if (n < 0)
// 	// {
// 	// 	n = -n;
// 	// 	written = write (fd, "-", 1);
// 	// }
// 	written += ft_hex_output(n, fd, c);
// 	return (written);
// }

int	ft_puthex_fd(unsigned long long n, int fd, char c)
{
	unsigned long long	digit;
	unsigned long long	buf;
	int					count;
	char				ch;

	count = 0;
	digit = 1;
	buf = n;
	while (n >= 16)
	{
		n /= 16;
		digit *= 16;
	}
	while (digit > 0)
	{
		ch = c_to_hex(buf / digit, c);
		count += write (fd, &ch, 1);
		buf %= digit;
		digit /= 16;
	}
	return (count);
}

char	c_to_hex(int n, char c)
{
	if (n < 10)
		return (n + '0');
	else
	{
		if (c == 'x')
			return (n + 'a' - 10);
		else
			return (n + 'A' - 10);
	}
}

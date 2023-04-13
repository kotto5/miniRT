/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_system.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 15:44:53 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/04 14:39:18 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_char(va_list *ap, int *sum)
{
	const char	c = va_arg(*ap, int);

	*sum += write(1, &c, 1);
}

void	print_str(va_list *ap, int *sum)
{
	const char	*s = va_arg(*ap, char *);

	if (s == NULL)
	{
		*sum += write(1, "(null)", 6);
		return ;
	}	
	*sum += write(1, s, ft_strlen(s));
}

void	print_pointer(va_list *ap, int *sum)
{
	*sum += write(1, "0x", 2);
	*sum += ft_puthex_fd(va_arg(*ap, unsigned long long), 1, 'x');
}

int	ft_putllnbr_fd(int long long n, int fd)
{
	int	i;

	i = 0;
	if (n == LLONG_MIN)
		return (write(1, "-9223372036854775808", 20));
	else if (n < 0)
	{
		n = -n;
		i = write (fd, "-", 1);
	}
	i += out_put_llnbr(n, fd);
	return (i);
}

int	out_put_llnbr(long long n, int fd)
{
	long long	digit;
	long long	buf;
	int			count;
	char		c;

	count = 0;
	digit = 1;
	buf = n;
	while (n >= 10)
	{
		n /= 10;
		digit *= 10;
	}
	while (buf >= 0 && digit > 0)
	{
		c = buf / digit + '0';
		count += write (fd, &c, 1);
		buf %= digit;
		digit /= 10;
	}
	return (count);
}

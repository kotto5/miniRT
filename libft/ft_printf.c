/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:00:55 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/04 14:35:37 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(char *format, ...)
{
	va_list	ap;
	int		sum;

	va_start(ap, format);
	sum = 0;
	output_format(format, &ap, &sum);
	va_end(ap);
	return (sum);
}

void	output_format(char *format, va_list *ap, int *sum)
{
	int	i;

	i = 0;
	while (format[i])
	{
		while (format[i] && format[i] != '%')
			*sum += write(1, format + i++, 1);
		if (format[i] == '%')
		{
			i += filter(format + i, ap, sum);
		}
	}
}

int	filter(char *format, va_list *ap, int *sum)
{
	if (format[1] == 'c')
		print_char(ap, sum);
	else if (format[1] == 's')
		print_str(ap, sum);
	else if (format[1] == 'd' || format[1] == 'i')
		*sum += ft_putllnbr_fd(va_arg(*ap, int), 1);
	else if (format[1] == 'u')
		*sum += ft_putllnbr_fd(va_arg(*ap, unsigned int), 1);
	else if (format[1] == 'p')
		print_pointer(ap, sum);
	else if (format[1] == 'x' || format[1] == 'X')
		*sum += ft_puthex_fd(va_arg(*ap, unsigned int), 1, format[1]);
	else if (format[1] == '%')
		*sum += write(1, format + 1, 1);
	else
		return (1);
	return (2);
}

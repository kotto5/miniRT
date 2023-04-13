/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 18:27:03 by kakiba            #+#    #+#             */
/*   Updated: 2022/12/04 14:43:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	out_put(int n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
		write (fd, "-2147483648", 11);
	else if (n < 0)
	{
		n = -n;
		write (fd, "-", 1);
	}
	out_put(n, fd);
}

static void	out_put(int n, int fd)
{
	int		i;
	int		j;
	int		buf;
	char	s[12];

	i = 1;
	buf = n;
	while (n >= 10)
	{
		n /= 10;
		i *= 10;
	}
	j = 0;
	while (buf >= 0 && i > 0)
	{
		s[j++] = buf / i + '0';
		buf %= i;
		i /= 10;
	}
	write(fd, s, j);
}

// int	main(void)
// {
// 	ft_putnbr_fd(81277172987122491, 1);
// }

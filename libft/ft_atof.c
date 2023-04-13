/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:26:11 by kakiba            #+#    #+#             */
/*   Updated: 2023/02/09 15:13:49 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	clc_mini_sum(char *str);

double	ft_atof(char *str)
{
	int		sign_flag;
	int		i;
	double	sum;

	i = 0;
	sign_flag = 1;
	sum = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
		sign_flag = -1;
	while (ft_isdigit(str[i]))
		sum = (str[i++] - '0') + (sum * 10);
	if (str[i] == '.')
		i++;
	sum += clc_mini_sum(&str[i]);
	return (sum * sign_flag);
}

// double	ft_atof(char *str)
// {
// 	int		sign_flag;
// 	int		i;
// 	double	sum;

// 	i = 0;
// 	sign_flag = 1;
// 	sum = 0;
// 	if (str[i] == '+')
// 	{
// 		sign_flag = 1;
// 		i++;
// 	}
// 	else if (str[i] == '-')
// 	{
// 		sign_flag = -1;
// 		i++;
// 	}
// 	while (ft_isdigit(str[i]))
// 	{
// 		sum = (str[i] - '0') + (sum * 10);
// 		i++;
// 	}
// 	if (str[i] == '.')
// 		i++;
// 	sum += clc_mini_sum(&str[i]);
// 	return (sum * sign_flag);
// }

static double	clc_mini_sum(char *str)
{
	int		i;
	int		digits;
	double	ret;

	i = 0;
	ret = 0;
	digits = 0;
	while (ft_isdigit(str[i]) && i < 7)
	{
		ret = (str[i] - '0') + (ret * 10);
		i++;
		digits++;
	}
	while (digits > 0)
	{
		ret /= 10;
		digits--;
	}
	return (ret);
}

// int	main()
// {
// 	char	*str;

// 	str = "12345";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "123.123";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "0.133";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "0.00123";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "1.2461";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "999.999";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "999.9983127949";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "0.13245132";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "00.3149329";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "-19083.4";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "-+19083.4";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// 	str = "+19083.4";
// 	if (ft_atof(str) != atof(str))
// 		printf("[%s]\n", str);
// }
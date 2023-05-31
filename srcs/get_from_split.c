/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/31 17:47:08 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static double	convert_range(int a)
{
	if (a > 255)
		return (1.0);
	return ((double)a / 255.0);
}
int	get_ref_from_split(char *str, t_reflect *ref)
{
	char			**split_tmp;
	t_bright_color	bcolor;

	split_tmp = ft_split(str, ',');
	if (get_size_double_ptr(split_tmp) != 3 \
		|| ft_isdigit_str(split_tmp[0], 0) == false \
		|| ft_isdigit_str(split_tmp[1], 0) == false \
		|| ft_isdigit_str(split_tmp[2], 0) == false)
	{
		free_double_ptr(split_tmp);
		return (ERROR);
	}
	bcolor.t = 0;
	bcolor.r = convert_range(ft_atoi(split_tmp[0]));
	bcolor.g = convert_range(ft_atoi(split_tmp[1]));
	bcolor.b = convert_range(ft_atoi(split_tmp[2]));
	ref->am = bcolor;
	ref->di = bcolor;
	ref->sp = bcolor;
	ref->sp_shininess = 2;
	ref->use_perfect_reflectance = false;
	free_double_ptr(split_tmp);
	return (SUCCESS);
}

int	get_vec_from_split(char *str, t_vec3 *vec)
{
	char	**split_tmp;

	split_tmp = ft_split(str, ',');
	if (get_size_double_ptr(split_tmp) != 3 \
		|| ft_isdouble(split_tmp[0]) == false \
		|| ft_isdouble(split_tmp[1]) == false \
		|| ft_isdouble(split_tmp[2]) == false)
	{
		free_double_ptr(split_tmp);
		return (ERROR);
	}
	vec->x = ft_atof(split_tmp[0]);
	vec->y = ft_atof(split_tmp[1]);
	vec->z = ft_atof(split_tmp[2]);
	free_double_ptr(split_tmp);
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clc4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:03:24 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/29 16:15:10 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

double	map(double v, double vmin, double vmax, double tmin, double tmax) // 値のマッピング
{
	v = tmin + ((tmax - tmin) * constrain(v, vmin, vmax) / (vmax - vmin));
	return (v);
}

t_reflect	get_t_refrect(t_bright_color am, t_bright_color di, t_bright_color sp, double sp_shininess, bool use_perfect_reflectance, t_bright_color perfect_reflectance)
{
	t_reflect	ref;

	ref.am = am;
	ref.di = di;
	ref.sp = sp;
	ref.sp_shininess = sp_shininess;
	ref.use_perfect_reflectance = use_perfect_reflectance;
	ref.perfect_reflectance = perfect_reflectance;
	return (ref);
}

void	print_vec(t_vec3 vec, char *str)
{
	printf("%s x is %f,  y is %f, z is %f\n", str, vec.x, vec.y, vec.z);
}

double	constrain(double v, double vmin, double vmax)
{
	if (v < vmin)
		return (vmin);
	if (v > vmax)
		return (vmax);
	return (v);
}
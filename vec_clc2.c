/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 06:42:05 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/27 15:07:38 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// ret = |vec1| * |vec1|
double	vec_mag_sq(t_vec3 va)
{
	return ((va.x * va.x) + (va.y * va.y) + (va.z * va.z));
}

// ret = |vec1|
double	vec_mag(t_vec3 va)
{
	return (sqrt(vec_mag_sq(va)));
}

void	set_vec3(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

t_vec3	vec_normilize(t_vec3 vec)
{
	return (vec_mult(vec, 1.0 / vec_mag(vec)));
}

t_vec3	get_vec(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
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

double	map(double v, double vmin, double vmax, double tmin, double tmax) // 値のマッピング
{
	v = tmin + ((tmax - tmin) * constrain(v, vmin, vmax) / (vmax - vmin));
	return (v);
}

// t_reflect	get_t_refrect(double am, double di, double sp, double sp_shininess)
// t_reflect	get_t_refrect(t_img_color am, t_img_color di, t_img_color sp, t_img_color sp_shininess)
// {
// 	t_reflect	ref;

// 	ref.am.color = am.color;
// 	ref.di.color = di.color;
// 	ref.sp.color = sp.color;
// 	ref.sp_shininess.color = sp_shininess.color;
// }

t_reflect	get_t_refrect(double am, double di, double sp, double sp_shininess)
{
	t_reflect	ref;

	ref.d_am = am;
	ref.d_di = di;
	ref.d_sp = sp;
	ref.d_sp_shininess = sp_shininess;
	return (ref);
}



/*
color	t  r  b  g
		ff 41 42 a5

color	t r g b
		

*/


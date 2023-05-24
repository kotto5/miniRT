/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 06:42:05 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/22 20:02:38 by kakiba           ###   ########.fr       */
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

t_vec3	vec_normalize(t_vec3 vec)
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

// t_reflect	get_t_refrect(double am, double di, double sp, double sp_shininess)
// {
// 	t_reflect	ref;

// 	ref.d_am = am;
// 	ref.d_di = di;
// 	ref.d_sp = sp;
// 	ref.sp_shininess = sp_shininess;
// 	return (ref);
// }



/*
color	t  r  b  g
		ff 41 42 a5

color	t r g b
		

*/


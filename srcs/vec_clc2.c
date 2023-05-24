/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 06:42:05 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/28 18:49:15 by kakiba           ###   ########.fr       */
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

t_vec3	vec_rotate(t_vec3 v, t_mat3 m) {
	t_vec3 result;
	result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z;
	result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z;
	result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z;
	return result;
}

t_mat3 multiply_matrices(t_mat3 a, t_mat3 b) {
    t_mat3 result;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }

    return result;
}

t_mat3 rotation_matrix(t_vec3 vec)
{
    double cx = cos(vec.x);
    double sx = sin(vec.x);
    double cy = cos(vec.y);
    double sy = sin(vec.y);
    double cz = cos(vec.z);
    double sz = sin(vec.z);

    t_mat3 rot_x = {
        .m = {
            {1, 0, 0},
            {0, cx, -sx},
            {0, sx, cx}
        }
    };

    t_mat3 rot_y = {
        .m = {
            {cy, 0, sy},
            {0, 1, 0},
            {-sy, 0, cy}
        }
    };

    t_mat3 rot_z = {
        .m = {
            {cz, -sz, 0},
            {sz, cz, 0},
            {0, 0, 1}
        }
    };

    // 回転行列を掛け合わせる関数が必要です。
    t_mat3 result = multiply_matrices(rot_z, multiply_matrices(rot_y, rot_x));
    return result;
}

t_vec3 direction_to_euler(t_vec3 direction)
{
    t_vec3 euler;
    euler.x = asin(direction.y);
    euler.y = atan2(-direction.x, direction.z);
    euler.z = 0; // ロール角は通常0とします（必要に応じて変更してください）

    return euler;
}

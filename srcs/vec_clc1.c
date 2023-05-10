/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_clc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 06:42:12 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/17 06:42:17 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// 視点位置
// 画像の二次元座標→空間の三次元変換
// 画像の座標 Xs, Ys から 三次元座標 Xw Yw Zw への変換
// Xw = 2Xs / (WIDTH-1) - 1.0
// Yw = 2Ys / (HEIGHT-1) - 1.0
// Zw = 0

// vec3 = vec1 + vec2
t_vec3	vec_add(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.x + vb.x;
	ans.y = va.y + vb.y;
	ans.z = va.z + vb.z;
	return (ans);
}

// vec3 = vec1 - vec2
t_vec3	vec_sub(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.x - vb.x;
	ans.y = va.y - vb.y;
	ans.z = va.z - vb.z;
	return (ans);
}

// vec3 = k * vec1
t_vec3	vec_mult(t_vec3 va, double k)
{
	t_vec3	ans;

	ans.x = va.x * k;
	ans.y = va.y * k;
	ans.z = va.z * k;
	return (ans);
}

// vec3 = vec1 ・ vec2
double	vec_dot(t_vec3 va, t_vec3 vb)
{
	return ((va.x * vb.x) + (va.y * vb.y) + (va.z * vb.z));
}

// vec3 = vec1 × vec2
t_vec3	vec_cross(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.y * vb.z - va.z * vb.y;
	ans.y = va.z * vb.x - va.x * vb.z;
	ans.z = va.x * vb.y - va.y * vb.x;
	return (ans);
}

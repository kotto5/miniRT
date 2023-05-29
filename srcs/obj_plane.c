/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:43:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/29 15:56:32 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// t は 判別式によっては二つ解をもつ。(この関数では、root 変数が判別式の役割)
// t が 正の値であるとき、ray は交点をもつということである。
// t が 二つの解を持ち、両方とも正ならば、ray は球を貫通していて、小さい方が手前、大きい方が奥側の貫通点である。
// 二つの解のうち、大きい方を返すと、呼び出す関数は奥側の値を計算するので、誤解を恐れずいうと、暗く見える。
static double	get_t_ray_plane(t_ray ray, t_plane *plane)
{
	double	denom;

	denom = vec_dot(ray.dir, plane->vertical);
	if (denom == 0.00)
		return (-1);
	return (vec_dot(vec_sub(plane->position, ray.pos), plane->vertical) / denom);
}

t_intersection	get_intersection_plane(const t_ray ray, const t_obj *obj)
{
	t_plane			*plane;
	t_intersection	intersection;
	double t;
	t_vec3	td;

	plane = obj->instance;
	intersection.does_intersect = false;
	t = get_t_ray_plane(ray, plane);
	if (t < 0)
		return (intersection);
	intersection.does_intersect = true;
	td = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, td);
	// intersection.distance = d;
	intersection.distance = vec_mag(td);
	intersection.vertical_dir = vec_normalize(plane->vertical);
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

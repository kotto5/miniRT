/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:42:42 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/31 18:58:24 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

double	get_minimum(double a, double b, double c)
{
	if (a <= b && a <= c)
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}

double	get_maximum(double a, double b, double c)
{
	if (a >= b && a >= c)
		return (a);
	else if (b >= a && b >= c)
		return (b);
	else
		return (c);
}

static double	get_t_ray_rect(t_ray ray, t_rect *rect)
{
	double	start;
	double	end;

	end = get_minimum((rect->bound2.x - ray.pos.x) / ray.dir.x, \
								(rect->bound2.y - ray.pos.y) / ray.dir.y, \
								(rect->bound2.z - ray.pos.z) / ray.dir.z);
	start = get_maximum((rect->bound1.x - ray.pos.x) / ray.dir.x, \
								(rect->bound1.y - ray.pos.y) / ray.dir.y, \
								(rect->bound1.z - ray.pos.z) / ray.dir.z);
	if (rect->bound1.x - ray.pos.x <= 0 && rect->bound2.x - ray.pos.x >= 0 && \
		rect->bound1.y - ray.pos.y <= 0 && rect->bound2.y - ray.pos.y >= 0 && \
		rect->bound1.z - ray.pos.z <= 0 && rect->bound2.z - ray.pos.z >= 0)
		return (true);
	if (start >= end)
		return (start);
	else
		return (-1);
}

t_intersection	get_intersection_rect(const t_ray ray, const t_obj *obj)
{
	t_rect			*rect;
	t_intersection	intersection;
	double			t;
	t_vec3			dt;

	rect = obj->instance;
	intersection.does_intersect = false;
	t = get_t_ray_rect(ray, rect);
	if (t < 0)
		return (intersection);
	else
	{
		intersection.does_intersect = true;
		return (intersection);
	}
	dt = vec_mult(ray.dir, t);
	intersection.does_intersect = true;
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	intersection.vertical_dir = vec_normalize(vec_sub(intersection.position, \
														ray.pos));
	return (intersection);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:42:42 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/01 15:54:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static double	get_ray_t_to_sphere(t_ray ray, t_sphere *sphere)
{
	const double	l_a = vec_mag_sq(ray.dir);
	const double	l_b = 2.0 * vec_dot(ray.dir, \
										(vec_sub(ray.pos, sphere->pos)));
	double			root;
	double			t1;
	double			t2;

	root = l_b * l_b \
			- (4.0 * l_a \
			* (vec_mag_sq(\
			vec_sub(ray.pos, sphere->pos)) - (sphere->r * sphere->r)));
	if (l_a == 0.0 || root < 0.0)
		return (-1);
	else
	{
		root = sqrt(root);
		t1 = (-1.0 * l_b + root) / (2.0 * l_a);
		t2 = (-1.0 * l_b - root) / (2.0 * l_a);
		if (t2 < 0 || (t1 > 0 && t1 < t2))
			return (t1);
		else
			return (t2);
	}
}

t_intersection	get_intersection_sphere(const t_ray ray, const t_obj *obj)
{
	t_sphere			*sphere;
	t_intersection		intersection;
	double				t;
	t_vec3				dt;

	sphere = obj->instance;
	ft_memset(&intersection, 0, sizeof(t_intersection));
	t = get_ray_t_to_sphere(ray, sphere);
	if (t < 0)
		return (intersection);
	dt = vec_mult(ray.dir, t);
	intersection.does_intersect = true;
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	intersection.vertical_dir = vec_normalize(vec_sub(intersection.position, \
														sphere->pos));
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

bool	is_inside_sphere(const t_obj *obj, const t_vec3 point)
{
	t_sphere	*sphere;
	t_vec3		pos_to_point;

	sphere = obj->instance;
	pos_to_point = vec_sub(point, sphere->pos);
	if (vec_mag_sq(pos_to_point) < sphere->r * sphere->r)
		return (true);
	return (false);
}

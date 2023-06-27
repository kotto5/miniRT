/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:42:42 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/27 23:03:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	solve_quadratic_equation(double a, double b, double c, double solution[2])
{
	double	root;

	root = b * b - (4.0 * a * c);
	if (a == 0.0 || root < 0.0)
		return (ERROR);
	root = sqrt(root);
	solution[0] = (-1.0 * b + root) / (2.0 * a);
	solution[1] = (-1.0 * b - root) / (2.0 * a);
	return (SUCCESS);
}

static double	get_ray_t_to_sphere(t_ray ray, t_sphere *sphere)
{
	const double	l_a = vec_mag_sq(ray.dir);
	const double	l_b = 2.0 * vec_dot(ray.dir, \
										(vec_sub(ray.pos, sphere->pos)));
	const double	l_c = (vec_mag_sq(\
			vec_sub(ray.pos, sphere->pos)) - (sphere->r * sphere->r));
	double			t[2];

	if (l_a == 0.0)
		return (-1);
	if (solve_quadratic_equation(l_a, l_b, l_c, t) == ERROR)
		return (-1);
	if (t[1] < 0 || (t[0] > 0 && t[0] < t[1]))
		return (t[0]);
	else
		return (t[1]);
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

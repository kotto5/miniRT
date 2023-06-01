/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:43:21 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/31 19:21:25 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	set_solutions(t_ray ray, t_cylinder *cylinder, double t[2])
{
	const t_vec3	l_p = vec_sub(ray.dir, \
									(vec_mult(cylinder->vertical, \
									vec_dot(ray.dir, cylinder->vertical))));
	const t_vec3	l_q = vec_sub(vec_sub(ray.pos, \
											cylinder->position), \
											vec_mult(cylinder->vertical, \
											vec_dot(vec_sub(ray.pos, \
													cylinder->position), \
													cylinder->vertical)));
	const double	l_a = vec_mag_sq(l_p);
	const double	l_b = 2 * vec_dot(l_p, l_q);
	const double	root = pow(l_b, 2) - 4 * l_a * (vec_mag_sq(l_q) \
							- pow(cylinder->r, 2));

	if (root < 0)
		return (ERROR);
	t[0] = (-1 * l_b + sqrt(root)) / (2 * l_a);
	t[1] = (-1 * l_b - sqrt(root)) / (2 * l_a);
	return (SUCCESS);
}

// dot < 0 == 円柱の下
// vecmug > height == 円柱の上
static bool	is_on_cylinder(t_ray ray, t_cylinder *cylinder, double t)
{
	const double	projection_length = vec_dot(vec_sub(\
												vec_add(ray.pos, \
													vec_mult(ray.dir, t)), \
														cylinder->position), \
												cylinder->vertical);
	const t_vec3	projection = vec_mult(cylinder->vertical, \
											projection_length);

	if (projection_length < 0.00)
		return (false);
	if (vec_mag(projection) > cylinder->height)
		return (false);
	return (true);
}

static int	get_t_ray_cylinder(t_ray ray, \
								t_cylinder *cylinder, \
								double *solution)
{
	double	t[2];
	bool	is_on[2];

	ft_memset(is_on, 0, sizeof(is_on));
	if (set_solutions(ray, cylinder, t))
		return (-1);
	if (t[0] < 0.0 && t[1] < 0.0)
		return (ERROR);
	else
	{
		if (t[0] > 0.0)
			is_on[0] = is_on_cylinder(ray, cylinder, t[0]);
		if (t[1] > 0.0)
			is_on[1] = is_on_cylinder(ray, cylinder, t[1]);
		if ((!is_on[0] && !is_on[1]))
			return (ERROR);
		else if (!is_on[1])
			*solution = t[0];
		else if (!is_on[0])
			*solution = t[1];
		else
			*solution = get_min_double(t[0], t[1]);
	}
	return (SUCCESS);
}

t_vec3	get_cylinder_normal(t_vec3 intersect, \
							t_vec3 vertical, \
							t_vec3 cylinder_center)
{
	t_vec3	to_center;
	double	projection_length;
	t_vec3	projection;
	t_vec3	normal;

	to_center = vec_sub(intersect, cylinder_center);
	projection_length = vec_dot(to_center, vertical);
	projection = vec_mult(vertical, projection_length);
	normal = vec_sub(to_center, projection);
	return (vec_normalize(normal));
}

t_intersection	get_intersection_cylinder(const t_ray ray, const t_obj *obj)
{
	t_cylinder		*cylinder;
	t_intersection	intersection;
	double			t;
	t_vec3			dt;

	cylinder = obj->instance;
	intersection.does_intersect = false;
	if (get_t_ray_cylinder(ray, cylinder, &t))
		return (intersection);
	intersection.does_intersect = true;
	dt = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	intersection.vertical_dir = get_cylinder_normal(intersection.position, \
													cylinder->vertical, \
													cylinder->position);
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

bool	is_inside_cylinder(const t_obj *obj, const t_vec3 point)
{
	(void)obj;
	(void)point;
	return (false);
}

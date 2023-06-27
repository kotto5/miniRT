/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/27 21:47:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// dot < 0 == 円柱の下
// vecmug > height == 円柱の上

static	int	solve_quadratic_equation(double a, double b, double c, double solution[2])
{
	const double	root = pow(b, 2) - 4 * a * c;

	if (root < 0)
		return (ERROR);
	t[0] = (-1 * b + sqrt(root)) / (2 * a);
	t[1] = (-1 * b - sqrt(root)) / (2 * a);
	return (SUCCESS);
}

static int	get_t_ray_cone(t_ray ray, \
								t_cone *cone, \
								double *solution)
{
	double	t[2];
	bool	is_on[2];

	ft_memset(is_on, 0, sizeof(is_on));

	t_vec3	h = vec_sub(cone->center, cone->tip);
	t_vec3	h_dir = vec_mult(h, vec_mag(h));

	double	dot_d_h = vec_dot(dir, h_dir);
	double	dotsq_d_h = dot_d_h * dot_d_h;

	double	m = (cone->r * cone->r) / vec_mag_sq(h);
	t_vec3	w = vec_sub(ray.pos, cone->tip);

	double	dot_w_h = vec_dot(dir, h_dir);
	double	dotsq_w_h = dot_w_h * dot_w_h;

	// double	a = vec_dot(cone->dir, cone->dir) - (m * dotsq_d_h) - (dotsq_d_h);
	// double	c = vec_dot(w, w) - (m * dotsq_w_h) - (dot_w_h);
	double	a = vec_dot(cone->dir, cone->dir) - ((m + 1) * dotsq_d_h);
	double	b = 2 * (vec_dot(cone->dir, w) - (m * dot_d_h * dot_w_h) - dot_d_h * dot_w_h);
	double	c = vec_dot(w, w) - ((m + 1) * dotsq_w_h);
	if (solve_quadratic_equation(a, b, c, t) == ERROR)
		return (ERROR);
	if ((t[0] < 0 && t[1] < 0))
		return (ERROR);

	if (t[0] >= 0 && t[0] < t[1])
		*solution = t[0];
	else
		*solution = t[1];
	return (SUCCESS);
}

t_intersection	get_intersection_cone(const t_ray ray, const t_obj *obj)
{
	t_cone			*cone;
	t_intersection	intersection;
	double			t;
	t_vec3			dt;
	t_vec3			to_center;

	cone = obj->instance;
	intersection.does_intersect = false;
	if (get_t_ray_cone(ray, cone, &t) == ERROR)
		return (intersection);
	intersection.does_intersect = true;
	dt = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	to_center = vec_sub(intersection.position, cone->position);
	intersection.vertical_dir = vec_normalize(vec_sub(to_center, vec_mult(\
		cone->vertical, vec_dot(to_center, cone->vertical))));
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

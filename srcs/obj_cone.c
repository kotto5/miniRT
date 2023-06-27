/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/28 00:53:41 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// dot < 0 == 円柱の下
// vecmug > height == 円柱の上

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

bool	func(t_vec3 int1, t_vec3 h, t_vec3 h_dir, t_vec3 tip)
{
	// return (ERROR);
	int1 = vec_sub(int1, tip);
	double	sol;
	sol = vec_dot(vec_sub(int1, h_dir), h);

	if (sol >= 0 && sol <= vec_mag(h))
		return (true);
	else
		return (false);
	if (sol > vec_mag(h))
		return (false);
	if (sol < 0)
		return (false);
	return (false);
}

static int	get_t_ray_cone(t_ray ray, \
								t_cone *cone, \
								double *solution)
{
	double	t[2];
	t[0] = 0;
	t[1] = 0;
	t_vec3	v = ray.dir;

	t_vec3	h = vec_sub(cone->center, cone->tip);
	t_vec3	h_dir = vec_mult(h, vec_mag(h));

	double	dot_v_h = vec_dot(v, h_dir);
	double	dotsq_v_h = dot_v_h * dot_v_h;

	double	m = (cone->r * cone->r) / vec_mag_sq(h);
	t_vec3	w = vec_sub(ray.pos, cone->tip);

	double	dot_w_h = vec_dot(w, h_dir);
	double	dotsq_w_h = dot_w_h * dot_w_h;

// cone->dir
	double	a = vec_dot(v, v) - (m * dotsq_v_h) - (dotsq_v_h);
	double	c = vec_dot(w, w) - (m * dotsq_w_h) - (dot_w_h);
	// double	a = vec_dot(v, v) - ((m + 1) * dotsq_d_h);
	double	b = 2 * (vec_dot(v, w) - (m * dot_v_h * dot_w_h) - dot_v_h * dot_w_h);
	// double	c = vec_dot(w, w) - ((m + 1) * dotsq_w_h);
	if (solve_quadratic_equation(a, b, c, t) == ERROR)
		return (ERROR);
	// printf("1!\n");
	// if ((t[0] < 0 && t[1] < 0))
	// 	return (ERROR);
	// printf("2!\n");

	if (t[0] >= 0 && func(vec_add(ray.pos, vec_mult(ray.dir, t[0])), h, h_dir, cone->tip))
		*solution = t[0];
	else if (t[1] >= 0 && func(vec_add(ray.pos, vec_mult(ray.dir, t[1])), h, h_dir, cone->tip))
		*solution = t[1];
	else
		return (ERROR);
	return (SUCCESS);
	// t_vec3	int1 = vec_mult(ray.dir, t[0]);
	// t_vec3	int2 = vec_mult(ray.dir, t[1]);

	// return (ERROR);

	// if (t[0] >= 0 && t[0] < t[1])
	// 	*solution = t[0];
	// else
	// 	*solution = t[1];
	// return (SUCCESS);
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
	// printf("GO!\n");
	intersection.does_intersect = true;
	dt = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	to_center = vec_sub(intersection.position, cone->center);
	intersection.vertical_dir = vec_normalize(vec_sub(to_center, vec_mult(\
		cone->dir, vec_dot(to_center, cone->dir))));
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

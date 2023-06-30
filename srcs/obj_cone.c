/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/30 11:09:27 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// dot < 0 == 円柱の下
// vecmug > height == 円柱の上

bool	func(t_vec3 int1, t_vec3 h, t_vec3 h_dir, t_vec3 H)
{
	const t_vec3	lint_h = vec_sub(int1, H);
	const double	sol = vec_dot(lint_h, h_dir);

	if (sol > vec_mag(h)) // below
		return (false);
	if (sol < 0) // above
		return (false);
	return (true);
}

static int	set_t(t_ray ray, \
								t_cone *cone, \
								double t[2])
{
	const double	dot_v_h = vec_dot(ray.dir, cone->dir);
	const double	dotsq_v_h = dot_v_h * dot_v_h;
	const double	m = (cone->r * cone->r) / vec_mag_sq(cone->center_to_tip);
	const t_vec3	w = vec_sub(ray.pos, cone->tip);
	const double	dot_w_h = vec_dot(w, cone->dir);

	if (solve_quadratic_equation(\
		vec_dot(ray.dir, ray.dir) - ((m + 1) * dotsq_v_h), \
		2 * (vec_dot(ray.dir, w) - \
			(m * dot_v_h * dot_w_h) - dot_v_h * dot_w_h), \
		vec_dot(w, w) - ((m + 1) * (dot_w_h * dot_w_h)), \
		t) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	set_valid_t_to_sol(t_ray ray, t_cone *cone, \
	double t[2], double *sol)
{
	bool	is_valid_t[2];

	sol[0] = false;
	sol[1] = false;
	if (t[0] >= 0 && func(vec_add(ray.pos, vec_mult(ray.dir, t[0])), \
		cone->center_to_tip, cone->dir, cone->tip))
		is_valid_t[0] = true;
	if (t[1] >= 0 && func(vec_add(ray.pos, vec_mult(ray.dir, t[1])), \
		cone->center_to_tip, cone->dir, cone->tip))
		is_valid_t[1] = true;
	if (is_valid_t[0] && is_valid_t[1])
		*sol = get_min_double(t[0], t[1]);
	else if (is_valid_t[0])
		*sol = t[0];
	else if (is_valid_t[1])
		*sol = t[1];
	else
		return (ERROR);
	return (SUCCESS);
}

static int	set_t_ray_cone(t_ray ray, \
								t_cone *cone, \
								double *sol)
{
	double	t[2];

	if (set_t(ray, cone, t) || set_valid_t_to_sol(ray, cone, t, sol))
		return (ERROR);
	return (SUCCESS);
}

t_intersection	get_intersection_cone( \
	const t_ray ray, const t_obj *obj)
{
	t_cone			*cone;
	t_intersection	intersection;
	double			t;
	t_vec3			dt;
	t_vec3			int_to_center;

	cone = obj->instance;
	intersection.does_intersect = false;
	if (set_t_ray_cone(ray, cone, &t) == ERROR)
		return (intersection);
	intersection.does_intersect = true;
	dt = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	int_to_center = vec_sub(intersection.position, cone->center);
	intersection.vertical_dir = vec_normalize(vec_sub(int_to_center, vec_mult(\
		vec_normalize(vec_sub(cone->center, cone->tip)), vec_dot(int_to_center, \
		vec_normalize(vec_sub(cone->center, cone->tip))))));
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
	return (intersection);
}

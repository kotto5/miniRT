/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/03 17:40:15 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// dot < 0 == 円柱の下
// vecmug > height == 円柱の上
static int	solve_quadratic_equation(\
	t_ray *ray, t_cone *cone, double solution[2])
{
	t_quandratic	qd;
	const double	m = (cone->r * cone->r) / vec_mag_sq(cone->height);
	const double	dot_v_h = vec_dot(ray->dir, cone->axis);
	const t_vec3	w = vec_sub(ray->pos, cone->tip);
	const double	dot_w_h = vec_dot(w, cone->axis);

	qd.a = vec_dot(ray->dir, ray->dir) - ((m + 1) * pow(dot_v_h, 2));
	qd.b = 2 * (vec_dot(ray->dir, w) \
		- (m * dot_v_h * dot_w_h) - dot_v_h * dot_w_h);
	qd.c = 4.0 * qd.a * (vec_dot(w, w) - ((m + 1) * (pow(dot_w_h, 2))));
	qd.root = qd.b * qd.b - qd.c;
	if (qd.a == 0.0 || qd.root < 0.0)
		return (ERROR);
	qd.root = sqrt(qd.root);
	solution[0] = (-1.0 * qd.b + qd.root) / (2.0 * qd.a);
	solution[1] = (-1.0 * qd.b - qd.root) / (2.0 * qd.a);
	return (SUCCESS);
}

static bool	is_in_range_of_cone(\
	t_vec3 int1, t_vec3 h, t_vec3 h_dir, t_vec3 tip)
{
	const t_vec3	lint_h = vec_sub(int1, tip);
	const double	sol = vec_dot(lint_h, h_dir);

	if (sol > vec_mag(h))
		return (false);
	if (sol < 0)
		return (false);
	return (true);
}

static int	get_t_ray_cone(t_ray ray, \
								t_cone *cone, \
								double *solution)
{
	double	t[2];
	bool	sol[2];

	cone->height = vec_sub(cone->center, cone->tip);
	cone->axis = vec_normalize(cone->height);
	sol[0] = false;
	sol[1] = false;
	ft_memset(t, 0, sizeof(double) * 2);
	if (solve_quadratic_equation(&ray, cone, t) == ERROR)
		return (ERROR);
	if (t[0] >= 0 && is_in_range_of_cone(vec_add(ray.pos, \
		vec_mult(ray.dir, t[0])), cone->height, cone->axis, cone->tip))
		sol[0] = true;
	if (t[1] >= 0 && is_in_range_of_cone(vec_add(ray.pos, \
		vec_mult(ray.dir, t[1])), cone->height, cone->axis, cone->tip))
		sol[1] = true;
	if (sol[0] && sol[1])
		*solution = get_min_double(t[0], t[1]);
	else if (sol[0])
		*solution = t[0];
	else if (sol[1])
		*solution = t[1];
	else
		return (ERROR);
	return (SUCCESS);
}

t_vec3	get_vert_cone(t_cone *cone, t_vec3 i)
{
	const t_vec3	p = cone->tip;
	const t_vec3	orient = vec_normalize(vec_sub(cone->center, cone->tip));
	const double	k = vec_mag(vec_sub(cone->center, cone->tip)) / cone->r;
	const double	dis = vec_mag(vec_sub(cone->center, p));
	const double	d = dis * sqrt(1.0 + pow(k, 2));

	return (vec_normalize(vec_sub(i, vec_add(p, vec_mult(orient, d)))));
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
	to_center = vec_sub(intersection.position, cone->center);
	intersection.vertical_dir = vec_normalize(vec_sub(to_center, vec_mult(\
		vec_normalize(vec_sub(cone->center, cone->tip)), \
		vec_dot(to_center, vec_normalize(vec_sub(cone->center, cone->tip))))));
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

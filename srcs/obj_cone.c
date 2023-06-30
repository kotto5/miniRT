/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:55:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/30 09:27:10 by kakiba           ###   ########.fr       */
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

bool	func(t_vec3 int1, t_vec3 h, t_vec3 cone->dir, t_vec3 H)
{
	t_vec3 Lint_h = vec_sub(int1, H);
	double	sol = vec_dot(Lint_h, cone->dir);
	(void)h;

	if (sol > vec_mag(h)) // below
		return (false);
	if (sol < 0) // above
		return (false);
	return (true);
}

static int	get_t(t_ray ray, \
								t_cone *cone, \
								double t[2])
{
	// t_vec3	h = vec_sub(cone->center, cone->tip);
	double	dot_v_h = vec_dot(ray.dir, cone->dir);
	double	dotsq_v_h = dot_v_h * dot_v_h;
	double	m = (cone->r * cone->r) / vec_mag_sq(cone->center_to_tip);
	t_vec3	w = vec_sub(ray.pos, cone->tip);
	double	dot_w_h = vec_dot(w, cone->dir);

	if (solve_quadratic_equation(\
		vec_dot(ray.dir, ray.dir) - ((m + 1) * dotsq_v_h), \
		2 * (vec_dot(ray.dir, w) - (m * dot_v_h * dot_w_h) - dot_v_h * dot_w_h), \
		vec_dot(w, w) - ((m + 1) * (dot_w_h * dot_w_h)), \
		t) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	get_t_ray_cone(t_ray ray, \
								t_cone *cone, \
								double *solution)
{
	double	t[2];
	bool	sol[2];
	sol[0] = false;
	sol[1] = false;

	if (get_t(ray, cone, t))
		return (ERROR);
	if (t[0] >= 0 && func(vec_add(ray.pos, vec_mult(ray.dir, t[0])), cone->center_to_tip, cone->dir, cone->tip))
		sol[0] = true;
	if (t[1] >= 0 && func(vec_add(ray.pos, vec_mult(ray.dir, t[1])), cone->center_to_tip, cone->dir, cone->tip))
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

t_vec3	get_vert_cone(t_cone *cone, t_vec3 I)
{
	t_vec3	P = cone->tip;
	t_vec3	orient = vec_normalize(vec_sub(cone->center, cone->tip));
	double	k = vec_mag(vec_sub(cone->center, cone->tip)) / cone->r;

	double	Dis = vec_mag(vec_sub(cone->center, P));
	double	D = Dis * sqrt(1.0 + pow(k, 2));
	t_vec3	A = vec_add(P, vec_mult(orient, D));
	t_vec3	Normal = vec_sub(I, A);
	return (vec_normalize(Normal));
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
		vec_normalize(vec_sub(cone->center, cone->tip)), vec_dot(to_center, vec_normalize(vec_sub(cone->center, cone->tip))))));
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);

}

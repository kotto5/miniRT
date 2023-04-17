/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cir1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:36 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/17 17:43:09 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// A = |VecRayDir|^2
// B = 2 * (VecRayDir . (VecRayP - VecCirP))
// C = (VecRayP - VecCirP)^2 - r^2
// 交差している座標 p = VecRayP + t*VecRayDir

double	get_ray_t_to_cir(t_ray ray, t_circle cir)
{
	double	A = vec_mag_sq(ray.dir);
	double	B = 2.0 * vec_dot(ray.dir, (vec_sub(ray.pos, cir.pos)));
	double	C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
	// printf("A:%f, B:%f C:%f\n", A, B, C);
	double	root = B * B - (4.0 * A * C);
	if (root < 0)
		return (-1);
	else
	{
		root = sqrt(root);
		double	t1 = (-B + root) / (2.0 * A);
		double	t2 = (-B - root) / (2.0 * A);
		// printf("t1:%f, t2:%f\n", t1, t2);
		if ((t1 >= 0 && (t1 <= t2) )|| t2 < 0)
			return (t1);
		else if (t2 >= 0)
			return (t2);
		return (-1);
	}
}

// double	get_ray_t_to_cir(t_ray ray, t_circle cir)
// {
// 	double	A = vec_mag_sq(ray.dir);
// 	double	B = 2 * vec_dot(ray.dir, vec_sub(ray.pos, cir.pos));
// 	double	C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
// 	double	root = B * B - (4.0 * A * C);
// 	if (root < 0)
// 		return (-1);
// 	else
// 		root = sqrt(root);
// 	double	t1 = (-1.0 * B) + (root / 2.0 / A);
// 	double	t2 = (-1.0 * B) - (root / 2.0 / A);
// 	if ((t1 >= 0 && (t1 <= t2) )|| t2 < 0)
// 		return (t1);
// 	else if (t2 >= 0)
// 		return (t2);
// 	return (-1);
// }

t_vec3	get_intersect_point_ray_cir(t_ray ray, double t)
{
	return (vec_add(vec_mult(ray.dir, t), ray.pos));
	// return (vec_sub(vec_mult(ray.dir, t), ray.pos));
	// return (vec_add(ray.pos, vec_mult(ray.dir, t)));
}

t_vec3	get_normal_cir(t_circle cir, t_vec3 surface_p)
{
	t_vec3	n_prime;

	n_prime = vec_sub(surface_p, cir.pos);
	return (vec_mult(n_prime, 1.0 / vec_mag(n_prime)));
}

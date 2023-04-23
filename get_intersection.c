#include "all.h"

static double	_get_ray_t_to_cir(t_ray ray, t_circle *cir)
{
	double	A = vec_mag_sq(ray.dir);
	double	B = 2.0 * vec_dot(ray.dir, (vec_sub(ray.pos, cir->pos)));
	double	C = vec_mag_sq(vec_sub(ray.pos, cir->pos)) - (cir->r * cir->r);
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

t_intersection	get_circle_intersection(const t_ray ray, const t_obj *obj)
{
	const t_circle_info *info = obj->instance;
	t_intersection		intersection;
	double				t;

	intersection.does_intersect = false; 
	t = _get_ray_t_to_cir(ray, (t_circle *)obj->instance);
	if (t < 0)
		return (intersection);
	intersection.does_intersect = true;
	intersection.position = vec_add(ray.pos, vec_mult(ray.dir, t));
	intersection.distance = vec_mag(vec_sub(ray.pos, info->pos));
	// intersection.vertical_dir = vec_normilize(vec_sub(intersection.position, info->pos));
	intersection.vertical_dir = vec_normilize(vec_sub(info->pos, intersection.position));
	return (intersection);
}

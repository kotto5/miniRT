#include "all.h"

bool	do_intersect_ray_and_square(t_ray ray, t_square sq)
{
	double	t = vec_dot(sq.n_dir, vec_sub(sq.pos, ray.pos)) / 
		vec_dot(ray.dir, sq.n_dir);

	if (t >= 0)
		return (1);
	else
		return (0);
}

#include "all.h"

double	get_minimum(double a, double b, double c)
{
	if (a <= b && a <= c )
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}

double	get_maximum(double a, double b, double c)
{
	if (a >= b && a >= c )
		return (a);
	else if (b >= a && b >= c)
		return (b);
	else
		return (c);
}


static double	get_t_ray_rect(t_ray ray, t_rect *rect)
{
	double	tx_start = (rect->bound1.x - ray.pos.x) / ray.dir.x;
	double	tx_end = (rect->bound2.x - ray.pos.x) / ray.dir.x;
	double	ty_start = (rect->bound1.y - ray.pos.y) / ray.dir.y;
	double	ty_end = (rect->bound2.y - ray.pos.y) / ray.dir.y;
	double	tz_start = (rect->bound1.z - ray.pos.z) / ray.dir.z;
	double	tz_end =(rect->bound2.z - ray.pos.z) / ray.dir.z;

	double	start = get_maximum(tx_start, ty_start, tz_start);
	double	end = get_minimum(tx_end, ty_end, tz_end);

// 実質plane （高さ0）のケースも込み
	if (rect->bound1.x - ray.pos.x <= 0 && rect->bound2.x - ray.pos.x >= 0 &&
		rect->bound1.y - ray.pos.y <= 0 && rect->bound2.y - ray.pos.y >= 0 &&
		rect->bound1.z - ray.pos.z <= 0 && rect->bound2.z - ray.pos.z >= 0)
		return (true);

	if (start >= end)
		return (start);
	else
		return (-1);
}

t_intersection	get_intersection_rect(const t_ray ray, const t_obj *obj)
{
	t_rect		*rect;
	t_intersection	intersection;
	double	t;
	t_vec3	dt;
	// t_vec3	td;
	// printf("Aa\n");

	rect = obj->instance;
	intersection.does_intersect = false;
	t = get_t_ray_rect(ray, rect);
	// printf("t[%f] \n", t);
	if (t < 0)
	{
		// printf("NOT !\n");
		return (intersection);
	}
	else
	{
		// printf("INTER! !\n");
		intersection.does_intersect = true;
		return (intersection);
	}

	dt = vec_mult(ray.dir, t);
	intersection.does_intersect = true;
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	intersection.vertical_dir = vec_normalize(vec_sub(intersection.position, ray.pos));
	return (intersection);
}

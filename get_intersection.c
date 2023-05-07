#include "all.h"

// t は 判別式によっては二つ解をもつ。(この関数では、root 変数が判別式の役割)
// t が 正の値であるとき、ray は交点をもつということである。
// t が 二つの解を持ち、両方とも正ならば、ray は球を貫通していて、小さい方が手前、大きい方が奥側の貫通点である。
// 二つの解のうち、大きい方を返すと、呼び出す関数は奥側の値を計算するので、誤解を恐れずいうと、暗く見える。

static double	get_ray_t_to_cir(t_ray ray, t_circle *cir)
{
	double	A = vec_mag_sq(ray.dir);
	double	B = 2.0 * vec_dot(ray.dir, (vec_sub(ray.pos, cir->pos)));
	double	C = vec_mag_sq(vec_sub(ray.pos, cir->pos)) - (cir->r * cir->r);
	double	root = B * B - (4.0 * A * C);

	if (A == 0 || root < 0)
		return (-1);
	else
	{
		root = sqrt(root);
		double	t1 = (-1.0 * B + root) / (2.0 * A);
		double	t2 = (-1.0 * B - root) / (2.0 * A);
		if (t1 < 0)
			return (t2);
		if (t2 < 0)
			return (t1);
		if (t1 <= t2)
			return (t1);
		else
			return (t2);
	}
}

t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj)
{
	const t_circle		*info = obj->instance;
	t_intersection		intersection;
	double				t;
	t_vec3				dt;

	intersection.does_intersect = false; 
	t = get_ray_t_to_cir(ray, (t_circle *)obj->instance);
	if (t < 0)
		return (intersection);
	intersection.does_intersect = true;
	dt = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	intersection.vertical_dir = vec_normilize(vec_sub(intersection.position, info->pos)); 

	return (intersection);
}

static double	get_t_ray_plane(t_ray ray, t_plane *plane)
{
	double	denom;
	double	t;

	denom = vec_dot(ray.dir, plane->vertical);
	if (denom == 0.00)
		return (-1);
	t = vec_dot(vec_sub(plane->position, ray.pos), plane->vertical) / denom;
	return (t);
}

// t_intersection	get_intersection_plane(t_vec3 eye_dir, t_vec3 eye_pos, t_vec3 vertical_plane)
t_intersection	get_intersection_plane(const t_ray ray, const t_obj *obj)
{
	t_plane			*plane;
	t_intersection	intersection;
	double t;
	t_vec3	td;

	plane = obj->instance;
	t = get_t_ray_plane(ray, plane);
	if (t >= 0)
	{
		intersection.does_intersect = true;
		td = vec_mult(ray.dir, t);
		intersection.position = vec_add(ray.pos, td);
		intersection.distance = vec_mag(td);
		intersection.vertical_dir = vec_normilize(plane->vertical);
		// if (t >= 2120.0)
		// {
		// 	printf("t is %f, distance %f, ", t, intersection.distance);
		// 	print_vec(intersection.position, "position");
		// }
	}
	else
		intersection.does_intersect = false;
	return (intersection);
}

// static double	get_t_ray_cylinder(t_ray ray, t_cylinder *cylinder)
// {
// 	t_vec3	vertical_vert = cos

// 	double A = pow(ray.dir.x, 2) + pow(ray.dir.y, 2);
// 	double B = 2 * (ray.dir.x * ray.pos.x + ray.dir.y * ray.pos.y);
// 	double C = pow(ray.pos.x, 2) + pow(ray.pos.y, 2) - pow(cylinder->r, 2);
// 	double root = pow(B, 2) - 4 * A * C;

// 	if (root < 0)
// 		return (-1);
// 	double t1 = (-B + sqrt(root)) / (2 * A);
// 	double t2 = (-B - sqrt(root)) / (2 * A);
// 	if (t1 < 0.0 && t2 < 0.0)
// 		return (t1);
// 	else if (t1 > 0.0 && ((t2 < 0.0) || (t1 < t2)))
// 		return (t1);
// 	else
// 		return (t2);
// }

static double	get_t_ray_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_vec3	P = vec_sub(ray.dir, (vec_mult(cylinder->vertical, vec_dot(ray.dir, cylinder->vertical))));
	t_vec3	Q = vec_sub(vec_sub(ray.pos, cylinder->position), vec_mult(cylinder->vertical, vec_dot(vec_sub(ray.pos, cylinder->position), cylinder->vertical)));
	double A = vec_mag_sq(P);
	double B = 2 * vec_dot(P, Q);
	double C = vec_mag_sq(Q) - pow(cylinder->r, 2);
	double root = pow(B, 2) - 4 * A * C;

	if (root < 0)
		return (-1);
	double t1 = (-B + sqrt(root)) / (2 * A);
	double t2 = (-B - sqrt(root)) / (2 * A);
	if (t1 < 0.0 && t2 < 0.0)
		return (t1);
	else if (t1 > 0.0 && ((t2 < 0.0) || (t1 < t2)))
		return (t1);
	else
		return (t2);
}

t_intersection	get_intersection_cylinder(const t_ray ray, const t_obj *obj)
{
	t_cylinder		*cylinder;
	t_intersection	intersection;
	double	t;
	t_vec3	dt;
	// t_vec3	td;

	cylinder = obj->instance;
	intersection.does_intersect = false;
	t = get_t_ray_cylinder(ray, cylinder);
	if (t < 0)
		return (intersection);
	dt = vec_mult(ray.dir, t);
	// if (!(10.0f > dt.z && dt.z > 3.0f))
	// 	return (intersection);
	intersection.does_intersect = true;
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	t_vec3	buf = cylinder->position;
	buf.z += dt.z;
	intersection.vertical_dir = vec_normilize(vec_sub(intersection.position, buf));
	return (intersection);
}

static double	get_minimum(double a, double b, double c)
{
	if (a <= b && a <= c )
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}


static double	get_maximum(double a, double b, double c)
{
	if (a >= b && a >= c )
		return (a);
	else if (b >= a && b >= c)
		return (b);
	else
		return (c);
}


// 直すこと

// rect bound1 >= bound2
// rect bound1 < bound2

// 0 ジョさん

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
	printf("t[%f] \n", t);
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
	intersection.vertical_dir = vec_normilize(vec_sub(intersection.position, ray.pos));
	return (intersection);
}

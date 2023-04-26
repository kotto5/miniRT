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

t_intersection	get_circle_intersection(const t_ray ray, const t_obj *obj)
{
	const t_circle		*info = obj->instance;
	t_intersection		intersection;
	double				t;
	t_vec3				test_dir;

	intersection.does_intersect = false; 
	t = get_ray_t_to_cir(ray, (t_circle *)obj->instance);
	if (t < 0)
		return (intersection);
	intersection.does_intersect = true;
	intersection.position = vec_add(ray.pos, vec_mult(ray.dir, t));

// distance に関してはどちらでも結果は変わらない。距離だから、そうだよね
	// intersection.distance = vec_mag(vec_sub(ray.pos, info->pos));
	intersection.distance = vec_mag(vec_sub(info->pos, ray.pos));

// この二つで結果が変わる。法線ベクトルのdir って正負関係なくない？
	intersection.vertical_dir = vec_normilize(vec_sub(intersection.position, info->pos)); 
	// intersection.vertical_dir = vec_normilize(vec_sub(info->pos, intersection.position));

	// test_dir = vec_normilize(vec_sub(info->pos, intersection.position));
	// print_vec(intersection.vertical_dir, "virtical dir");
	// print_vec(intersection.vertical_dir, "test virtical dir");

	double	r_test = vec_mag(vec_sub(intersection.position, info->pos));
	printf("return intersect position:[%f,%f,%f], [obj r = %f, test r = %f]\n", intersection.position.x, intersection.position.y, intersection.position.z, info->r, r_test);

	return (intersection);
}

#include "all.h"
#include <math.h>

#define EPSILON 0.001

t_dlist	*get_light_list(t_dlist **gb_list)
{
	t_dlist	*light_list;

	light_list = NULL;

	// ft_dlstadd_back(&light_list, ft_dlstnew(
	// 	new_light(L_POINT, make_point_light_info(get_vec(-5, 5, -5), b_color_get(0, 0.5, 0.5, 0.5), gb_list), gb_list)));
	// ft_dlstadd_back(&light_list, ft_dlstnew(
	// 	new_light(L_POINT, make_point_light_info(get_vec(-5, 0, -5), b_color_get(0, 0.5, 0.5, 0.5), gb_list), gb_list)));
	// ft_dlstadd_back(&light_list, ft_dlstnew( 
	// 	new_light(L_POINT, make_point_light_info(get_vec(-5, 20, -5), b_color_get(0, 0.5, 0.5, 0.5), gb_list), gb_list)));

	// ft_dlstadd_back(&light_list, ft_dlstnew(
	// 	new_light(L_POINT, make_point_light_info(get_vec(0, 0.9, 2.5), b_color_get(0, 1.0, 1.0, 1.0), gb_list), gb_list)));

	// ft_dlstadd_back(&light_list, ft_dlstnew(
	// 	new_light(L_POINT, make_point_light_info(get_vec(0, 0.1, -2.5), b_color_get(0, 1.0, 1.0, 1.0), gb_list), gb_list)));

	// ft_dlstadd_back(&light_list, ft_dlstnew(
	// 	new_light(L_POINT, make_point_light_info(get_vec(0.5, 0.1, -2.5), b_color_get(0, 1.0, 1.0, 1.0), gb_list), gb_list)));

	// ft_dlstadd_back(&light_list, ft_dlstnew(
	// 	new_light(L_POINT, make_point_light_info(get_vec(-0.25, 0.5, -1), b_color_get(0, 1.0, 1.0, 1.0), gb_list), gb_list)));

	ft_dlstadd_back(&light_list, ft_dlstnew(
		new_light(L_POINT, make_point_light_info(get_vec(2, 1.5, 0.9), b_color_get(0, 1.0, 1.0, 1.0), gb_list), gb_list)));

	return (light_list);
}

static t_bright_color	get_ambient_ref_double6(t_reflect ref, t_lighting lighting)
{
	return (b_color_mult(ref.am, lighting.intensity));
	// return (ref.d_am * lighting.d_intensity);
}

// deffuse refrection ... 乱反射。光がランダムな方向に分散して反射する
// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di)
// double	get_deffsuse_ref(t_point_light light, t_circle cir, t_vec3 point)
// 入射ベクトル incident は、計算の都合上、入射する方向の逆を取る。
// 光源をp 交点をa とすると、 p - a が入射ベクトル。

	/*
	0 <= cos <= 1
	intensity ..? この流れだと 0 <= intensity <= 1
	0 <= di <= 1 だし、 di = 1 - am - sp;
	return の因数が、全て 0 <= x <= 1 なら、 di = 1 - am - sp; だから、和が1 を超えることはない。
	*/

static t_bright_color	get_deffsuse_ref6(t_intersection intersection, t_reflect ref, t_lighting lighting)
{
	double	cos_incident_and_vertical;

	cos_incident_and_vertical = vec_dot(intersection.vertical_dir, lighting.incident_to_light);
	if (cos_incident_and_vertical < 0)
		return (b_color_get(0, 0, 0, 0));
	// return (ref.d_di * lighting.d_intensity * cos_incident_and_vertical);
	return (b_color_mult_constant(b_color_mult(ref.di, lighting.intensity), cos_incident_and_vertical));
}

// 鏡面反射光の放射強度Rs
// Rs = Ks * Ii * cos^αθ
// 	  = Ks * Ii * (VecV ・　VecR)^α

// Ks: 鏡面反射係数（obj 依存）
// Ii: 入射光の強度 (light 依存)
// VecV は視野ベクトルの逆ベクトル	(ray と point)		方向ベクトル(正規化)
// VecR は入射光の正反射ベクトル	(light と point)	方向ベクトル(正規化)
// θ はVecV と VecR のなす角 (どうやって計算するんや？)
// α は光沢度（obj 依存） 1 <= α
// |VecV| = |VecR| = 1 (VecV と VecR は正規化する) Rs についてのでは、あくまで方向ベクトル
// 

// 二つの位置ベクトルにおいて、一点から一点に対するベクトルを取得する方法
// BA = OA - OB
// 感覚 向けたい方向(BA なら A) の位置ベクトル(OA) に対して、始点にしたいベクトル(OB)を指定する。


// double	get_specular_ref(t_point_light light, t_circle cir, t_vec3 intersection, t_ray eye)
static t_bright_color	get_specular_ref6(t_lighting lighting, t_intersection intersection, t_ray eye, t_reflect ref_info)
{
	// double	ref = 0;
	// double	Ks = ref_info.d_sp;
	// double	Ii = lighting.d_intensity;
	double	alpha = ref_info.sp_shininess;

	t_vec3	inverse_eyedir = vec_mult(eye.dir, -1);

	t_vec3	vertical = intersection.vertical_dir;
	// t_vec3	vecL = get_light_incident_dir(light, intersection);
	// t_vec3	incident = vec_normilize(vec_sub(light.pos, intersection.position));
	t_vec3	incident = lighting.incident_to_light;
	t_vec3	regular_ref_incident = vec_sub( vec_mult(vertical, 2.0 * vec_dot(vertical, incident)), incident);
	if (vec_dot(vertical, incident) < 0)
	{
		// printf("===============");
		return (b_color_get(0, 0, 0, 0));
	}
	double	inner_product = vec_dot(inverse_eyedir, regular_ref_incident);
	if (inner_product < 0)
		inner_product = 0;
	if (inner_product > 1)
		inner_product = 1;
	// ref = Ks * Ii * pow(inner_product, alpha);
	return (b_color_mult_constant(b_color_mult(ref_info.sp, lighting.intensity), pow(inner_product, alpha)));
}

// 半直線との交差判定の方法は　対象の形状ごとに異なる。
// しかし、どの方法であっても、交差判定に結果として交点の位置や交点における法線方向がわかれば
// 陰影の計算が可能である。
static t_bright_color	get_ref6(t_intersection intersection, t_reflect ref_info, t_lightsource *light, t_ray eye)
{
	t_bright_color		ref;

	t_lighting		lighting = light->lighting_at(intersection.position, light);

	ref = b_color_get(0, 0, 0, 0);
	ref = b_color_add(ref, get_ambient_ref_double6(ref_info, lighting));
	ref = b_color_add(ref, get_deffsuse_ref6(intersection, ref_info, lighting));
	ref = b_color_add(ref, get_specular_ref6(lighting, intersection, eye, ref_info));
	if (ref.r > 1.0)
	{
		// printf("ref is over 1   ref:%f", ref.r);
		// print_vec(intersection.position, "intersection position");
		// exit(1);
	}
	return (ref);
}

t_intersection_info	*get_nearest_intersection(t_scene *scene, t_ray *ray)
{
	t_dlist			*node;
	t_obj			*obj_content;
	t_intersection	tmp;
	t_intersection_info	*info;

	info = malloc(sizeof(t_intersection_info));
	ft_memset(info, 0, sizeof(t_intersection_info));
	node = scene->obj_list;
	info->intersection.does_intersect = false;
	while (node)
	{
		obj_content = node->content;
		// if (obj_content->type == O_CIRCLE)
		// 	usleep(1);
		tmp = obj_content->get_intersection(*ray, obj_content);
		if (tmp.does_intersect && (info->intersection.does_intersect == false || tmp.distance < info->intersection.distance))
		{
			info->intersection = tmp;
			info->obj = obj_content;
		}
		node = node->next;
	}
	return (info);
}

// bool	do_through_other_obj_by_light(t_dlist *obj_list, t_lighting lighting, t_vec3 intersect, t_obj *target)
// {
// 	t_dlist	*node;
// 	t_obj	*instance;
// 	t_ray	light_ray;
// 	t_intersection	intersection;

// 	light_ray.dir = lighting.incident_to_light;
// 	light_ray.pos = intersect;
// 	node = obj_list;
// 	while (node)
// 	{
// 		instance = node->content;
// 		if (instance == target)
// 		{
// 			node = node->next;
// 			continue ;
// 		}
// 		intersection = instance->get_intersection(light_ray, instance);
// 		if (intersection.does_intersect && intersection.distance < lighting.distance)
// 		{
// 			return (true);
// 		}
// 		node = node->next;
// 	}
// 	return (false);
// }

bool	do_through_other_obj_by_light(t_dlist *obj_list, t_lightsource *light, t_intersection_info *info)
{
	t_dlist	*node;
	t_obj	*instance;
	t_ray	light_ray;
	t_intersection	intersection;
	t_lighting		lighting = light->lighting_at(info->intersection.position, light);
	double			epsilon = 1.0 / 32;

	light_ray.dir = lighting.incident_to_light;
	light_ray.pos = info->intersection.position;
	lighting.distance += epsilon; // これで弾くのって instance == info->obj のケースじゃないの？
	node = obj_list;
	while (node)
	{
		instance = node->content;
		if (instance == info->obj)
		{
			node = node->next;
			continue ;
		}
		intersection = instance->get_intersection(light_ray, instance);
		if (intersection.does_intersect && intersection.distance < lighting.distance)
		{
			return (true);
		}
		node = node->next;
	}
	return (false);
}

t_bright_color	*ray_trace(t_scene *scene, t_ray *ray);

t_bright_color	get_color_with_at(t_scene *scene, t_intersection_info *info, t_lightsource *light, t_ray *ray)
{
	t_bright_color	ref;
	// t_lighting		lighting;
	// t_ray			reflect_ray;
	// t_bright_color	*ret;
	ft_memset(&ref, 0, sizeof(t_bright_color));

	if (info->intersection.does_intersect == true)
	{
		if (do_through_other_obj_by_light(scene->obj_list, light, info))
		{
			return (ref);
		}
		else
			ref = get_ref6(info->intersection, info->obj->ref, light, *ray);
	}
	return (ref);
}


t_bright_color	*ray_trace_ref(t_scene *scene, t_ray *ray, size_t times)
{
	t_bright_color		*b_color;
	t_intersection_info	*info;
	t_dlist				*node;

	if (times > 4)
		return (NULL);
	b_color = NULL;
	info = get_nearest_intersection(scene, ray);
	if (info->intersection.does_intersect)
	{
		b_color = ft_calloc(sizeof(t_bright_color), 1);
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, get_color_with_at(scene, info, node->content, ray));
			// *b_color = b_color_add(*b_color, get_color_with_at(*ray, info->intersection, node->content, info->obj));
			node = node->next;
		}
		if (info->obj->ref.use_perfect_reflectance)
		{
			t_ray			re_ray;
			t_bright_color	*ret;
			t_vec3			v;
			t_vec3			v2;
			double			dot_product;
			v = vec_mult(ray->dir, -1);
			v2 = vec_normilize(info->intersection.vertical_dir);
			dot_product = vec_dot(v2, v);
			if (dot_product < 0.0)
				return (b_color);
			re_ray.dir = vec_sub(vec_mult(v2, 2.0 * dot_product), v);
			re_ray.pos = vec_add(info->intersection.position, vec_mult(re_ray.dir, EPSILON));
			ret = ray_trace_ref(scene, &re_ray, times + 1);
			if (ret)
			{
				*ret = b_color_mult(*ret, info->obj->ref.perfect_reflectance);
				*b_color = b_color_add(*b_color, *ret);
			}
		}
	}
	return (b_color);
}

t_bright_color	*ray_trace(t_scene *scene, t_ray *ray)
{
	t_bright_color		*b_color;
	t_intersection_info	*info;
	t_dlist				*node;

	b_color = NULL;
	info = get_nearest_intersection(scene, ray);
	if (info->intersection.does_intersect)
	{
		b_color = ft_calloc(sizeof(t_bright_color), 1);
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, get_color_with_at(scene, info, node->content, ray));
			// *b_color = b_color_add(*b_color, get_color_with_at(*ray, info->intersection, node->content, info->obj));
			node = node->next;
		}
		if (info->obj->ref.use_perfect_reflectance)
		{
			t_ray			re_ray;
			t_bright_color	*ret;
			t_vec3			v;
			t_vec3			v2;
			double			dot_product;
			v = vec_mult(ray->dir, -1);
			v2 = vec_normilize(info->intersection.vertical_dir);
			dot_product = vec_dot(v2, v);
			if (dot_product < 0.0)
				return (b_color);
			re_ray.dir = vec_sub(vec_mult(v2, 2.0 * dot_product), v);
			re_ray.pos = vec_add(info->intersection.position, vec_mult(re_ray.dir, EPSILON));
			ret = ray_trace_ref(scene, &re_ray, 0);
			if (ret)
			{
				*ret = b_color_mult(*ret, info->obj->ref.perfect_reflectance);
				*b_color = b_color_add(*b_color, *ret);
			}
		}
	}
	return (b_color);
}

// int	*make_img6(t_img *img, t_ray eye, t_dlist **gb_list)
int	*make_img6(t_env *env)
{
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &env->img.endian);

	
	t_vec3			vec_win;
	t_img_color		color;
	t_bright_color	*ref_color;

	t_scene			scene;
	scene.obj_list = get_obj_list(&env->gb_list);
	scene.light_list = get_light_list(&env->gb_list);

	int	x;
	int	y = 0;
	// t_dlist	*node;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = get_screen_vec(x, y, env->eye);
			env->eye.dir = vec_normilize(vec_sub(vec_win, env->eye.pos));
			ref_color = ray_trace(&scene, &env->eye);
			if (ref_color == NULL)
				color.color = BACK_COLOR;
			else
				color = to_img_color_from_b_color(*ref_color);
			mlx_put_to_img(&env->img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (NULL);
}


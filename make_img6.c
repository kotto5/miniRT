#include "all.h"

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

	// if (do_through_other_obj_by_light(objs, incident))
	// 	return (0);
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
	double	alpha = ref_info.d_sp_shininess;

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
	// double			ref;
	t_bright_color		ref;

	ref_info.am = b_color_get(0.00, 0.01, 0.01, 0.01);
	ref_info.di = b_color_get(0.00, 0.69, 0.10, 0.05);
	ref_info.sp = b_color_get(0.00, 0.30, 0.05, 0.05);
	// ref_info.sp = b_color_get(0.00, 0.30, 0.30, 0.30);

	t_lighting		lighting = light->lighting_at(intersection.position, light);
	ref = b_color_get(0, 0, 0, 0);
	ref = b_color_add(ref, get_ambient_ref_double6(ref_info, lighting));
	ref = b_color_add(ref, get_deffsuse_ref6(intersection, ref_info, lighting));
	ref = b_color_add(ref, get_specular_ref6(lighting, intersection, eye, ref_info));
	// if (ref > 1.0)
	// {
	// 	printf("ref is over 1   ref:%f", ref);
	// 	print_vec(intersection.position, "intersection position");
	// 	exit(1);
	// }
	return (ref);
}

unsigned int	get_color_with_at(t_ray eye, t_intersection intersection, t_lightsource *light, t_obj *obj)
{
	t_circle		*circle;
	t_plane			*plane;
	t_bright_color	ref;
	t_reflect		obj_reflect;
	t_img_color		color;

	if (obj->type == O_CIRCLE)
	{
		circle = obj->instance;
		obj_reflect = circle->ref;
	}
	else if (obj->type == O_PLANE)
	{
		plane = obj->instance;
		obj_reflect = plane->ref;
	}
	if (intersection.does_intersect == true)
	{
		ref = get_ref6(intersection, obj_reflect, light, eye);
		color =  to_img_color_from_b_color(ref);
		// printf("%x %x %x %x\n", color.trgb.t, color.trgb.r, color.trgb.g, color.trgb.b);
		return (color.color);
	}
	else
	{
		// printf("FALSE\n");
		return (BACK_COLOR);
	}
}

int	*make_img6(t_img *img, t_ray eye, t_dlist **gb_list)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

	t_obj			*obj_content;
	t_dlist			*obj_list;
	obj_list = NULL;
	t_intersection 	intersection;
	t_vec3			vec_win;
	// t_img_color		color;
	// t_lightsource	*light = new_light(L_POINT, make_point_light_info(get_vec(-5, 5, -5), 1, gb_list), gb_list);
	t_lightsource	*light = new_light(L_POINT, make_point_light_info(get_vec(-5, 5, -5), b_color_get(0, 0.2, 0, 0), gb_list), gb_list);

	t_obj	*circle;
	circle = new_obj(O_CIRCLE, make_circle_instance(get_vec(0, 0, 5), 1, get_t_refrect(0.01, 0.69, 0.3, 2), gb_list), gb_list);

	t_obj	*circle2;
	circle2 = new_obj(O_CIRCLE, make_circle_instance(get_vec(1, 0, 8), 1, get_t_refrect(0.01, 0.69, 0.3, 2), gb_list), gb_list);
// circle = new_obj(O_CIRCLE, make_circle_instance(get_vec(0, 0, 5), 1, get_t_refrect(0, 1, 0, 0.0), gb_list), gb_list);
	// circle = new_obj(O_CIRCLE, make_circle_instance(get_vec(0, 0, 5), 1, get_t_refrect(0, 1, 0, 0.0), gb_list), gb_list);
	t_obj	*plane1;
	plane1 = new_obj(O_PLANE, make_plane_instance(vec_normilize(get_vec(0, 1, 0)), get_t_refrect(0.00, 0.0, 0.0, 2), gb_list), gb_list);
	// plane1 = new_obj(O_PLANE, make_plane_instance(vec_normilize(get_vec(0, 1, 0)), get_t_refrect(0.01, 0.69, 0.3, 2), gb_list), gb_list);
	// plane1 = new_obj(O_PLANE, make_plane_instance(get_vec(1, 1, 0), get_t_refrect(0.01, 0.69, 0.3, 2), gb_list), gb_list);
	// plane1 = new_obj(O_PLANE, make_plane_instance(get_vec(0, 0, 1), get_t_refrect(0.01, 0.69, 0.3, 2), gb_list), gb_list);

	ft_dlstadd_back(&obj_list, ft_dlstnew(circle));
	ft_dlstadd_back(&obj_list, ft_dlstnew(circle2));
	ft_dlstadd_back(&obj_list, ft_dlstnew(plane1));

	int	x;
	int	y = 0;
	t_dlist	*node;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = get_screen_vec(x, y, eye);
			eye.dir = vec_normilize(vec_sub(vec_win, eye.pos));
			node = obj_list;
			while (node)
			{
				obj_content = node->content;
				intersection = obj_content->get_intersection(eye, obj_content);
				if (intersection.does_intersect)
				{
					mlx_put_to_img(img, x, y, get_color_with_at(eye, intersection, light, obj_content));
					break ;
				}
				node = node->next;
			}
			if (node == NULL)
				mlx_put_to_img(img, x, y, BACK_COLOR);
			x++;
		}
		y++;
	}
	return (NULL);
}

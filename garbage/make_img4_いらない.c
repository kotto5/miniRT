// #include "all.h"

// int	make_white_color(double bright)
// {
// 	t_img_color	color;

// 	color.trgb.t = 0;
// 	color.trgb.r = bright;
// 	color.trgb.g = bright;
// 	color.trgb.b = bright;
// 	return (color.color);
// }

// // t_sphere	*make_sphere(t_vec3 origin, double r, t_dlist **gb_list)
// // {
// // 	t_sphere	*sphere;

// // 	sphere = ft_galloc(sizeof(t_sphere), gb_list);
// // 	if (!sphere)
// // 		return (NULL);
// // 	sphere->pos = origin;
// // 	sphere->r = r;
// // 	sphere->ref.am = 0.01;
// // 	sphere->ref.di = 0.69;
// // 	// sphere->ref.di = 1.00;
// // 	sphere->ref.sp = 0.3;
// // 	sphere->ref.sp_shininess = 8;
// // 	sphere->vertical = get_cir_vertical_dir;
// // 	return (sphere);
// // }

// // t_obj	*make_obj_sphere(t_vec3 origin, double r, t_dlist **gb_list)
// // {
// // 	t_obj		*obj;
// // 	t_sphere	*sphere;

// // 	sphere = ft_galloc(sizeof(t_sphere), gb_list);
// // 	if (sphere == NULL)
// // 		return (NULL);
// // 	sphere->pos = origin;
// // 	sphere->r = r;
// // 	sphere->ref.am = 0.01;
// // 	sphere->ref.di = 0.69;
// // 	// sphere->ref.di = 1.00;
// // 	sphere->ref.sp = 0.3;
// // 	sphere->ref.sp_shininess = 8;
// // 	sphere->vertical = get_cir_vertical_dir;
// // 	obj = ft_galloc(sizeof(t_obj), gb_list);
// // 	if (obj == NULL)
// // 		return (NULL);
// // 	obj->type = O_SPHERE;
// // 	obj->instance = sphere;
// // 	obj->get_intersection = get_intersection_sphere;
// // 	return (obj);
// // }

// // int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
// // {
// // 	t_obj	*sphere;
// // 	// void	*instance;

// // 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
// // 		&img->line_length, &img->endian);
// // 	// instance = make_sphere(get_vec3(0, 0, 5), 1, gb_list);
// // 	// if (!instance)
// // 	// 	return (NULL);
// // 	// sphere = new_obj(O_SPHERE, instance, gb_list);

// // 	sphere = make_obj_sphere(get_vec(0, 0, 5), 1, gb_list);
// // 	t_intersection inter;

// // 	inter = sphere->get_intersection(eye, sphere);
// // 	printf("%f, ", inter.distance);
// // 	print_vec(inter.position, "position");
// // 	print_vec(inter.vertical_dir, "vertical");

	
// // 	return (NULL);
// // }


// // t_img_color	get_ambient_ref2(t_reflect ref, t_point_light light)
// // {
// // 	t_img_color	color;

// // 	color.trgb.t = ref.am.trgb.t * light.intensity.trgb.t * 100;
// // 	color.trgb.r = ref.am.trgb.r * light.intensity.trgb.r * 100;
// // 	color.trgb.g = ref.am.trgb.g * light.intensity.trgb.g * 100;
// // 	color.trgb.b = ref.am.trgb.b * light.intensity.trgb.b * 100;
// // 	return (color);
// // }

// double	get_ambient_ref_double(t_reflect ref, t_point_light light)
// {
// 	return (ref.d_am * light.d_intensity);
// }

// // t_img_color	get_deffsuse_ref2(t_intersection intersection, t_reflect ref, t_point_light light)
// // {
// // 	double	cos;
// // 	t_vec3	n;
// // 	t_vec3	l;
// // 	t_img_color	color;

// // 	color.color = 0;
// // 	n = intersection.vertical_dir;
// // 	l = vec_normilize(vec_sub(light.pos, intersection.position));
// // 	cos = vec_dot(n, l);
// // 	if (cos < 0)
// // 		return (color);
// // 	color.trgb.t = light.intensity.trgb.t * ref.di.trgb.t * cos * 100;
// // 	color.trgb.r = light.intensity.trgb.r * ref.di.trgb.r * cos * 100;
// // 	color.trgb.g = light.intensity.trgb.g * ref.di.trgb.g * cos * 100;
// // 	color.trgb.b = light.intensity.trgb.b * ref.di.trgb.b * cos * 100;
// // 	return (color);
// // }

// // t_img_color	get_specular_ref2(t_point_light light, t_sphere cir, t_vec3 intersection, t_ray eye)
// // t_img_color	get_specular_ref2(t_point_light light, t_intersection intersection, t_ray eye, t_reflect ref_info)
// // {
// // 	t_img_color	ref;

// // // 入射ベクトル ray と交点
// // 	t_vec3	vecV = vec_normilize(vec_mult(eye.dir, -1));

// // // vecR
// // 	t_vec3	vecN = intersection.vertical_dir;
// // 	t_vec3	vecL = vec_normilize(vec_sub(light.pos, intersection.position));
// // 	t_vec3	vecR = vec_sub( vec_mult(vecN, 2.0 * vec_dot(vecN, vecL)), vecL);

// // 	double	inner_product = vec_dot(vecV, vecR);
// // 	if (inner_product < 0)
// // 		inner_product = 0;
// // 	if (inner_product > 1)
// // 		inner_product = 1;
// // 	ref.trgb.t = light.intensity.trgb.t * pow(inner_product, ref_info.sp_shininess.trgb.t) * ref_info.sp.trgb.t * 100;
// // 	ref.trgb.r = light.intensity.trgb.r * pow(inner_product, ref_info.sp_shininess.trgb.r) * ref_info.sp.trgb.r * 100;
// // 	ref.trgb.g = light.intensity.trgb.g * pow(inner_product, ref_info.sp_shininess.trgb.g) * ref_info.sp.trgb.g * 100;
// // 	ref.trgb.b = light.intensity.trgb.b * pow(inner_product, ref_info.sp_shininess.trgb.b) * ref_info.sp.trgb.b;
// // 	return (ref);
// // }


// // deffuse refrection ... 乱反射。光がランダムな方向に分散して反射する
// // double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di)
// // double	get_deffsuse_ref(t_point_light light, t_sphere cir, t_vec3 point)
// // 入射ベクトル incident は、計算の都合上、入射する方向の逆を取る。
// // 光源をp 交点をa とすると、 p - a が入射ベクトル。
// double	get_deffsuse_ref(t_intersection intersection, t_reflect ref, t_point_light light)
// {
// 	double	cos_incident_and_vertical;

// 	t_vec3	incident;
// 	incident = vec_normilize(vec_sub(light.pos, intersection.position));
// 	// if (do_through_other_obj_by_light(objs, incident))
// 	// 	return (0);
// 	cos_incident_and_vertical = vec_dot(intersection.vertical_dir, incident);
// 	if (cos_incident_and_vertical < 0)
// 		return (0);
// 	// print_vec(l, "deff");
// 	// printf("ans [%f] n", ref.d_di * light.d_intensity * cos_incident_and_vertical);
// 	/*
// 	0 <= cos <= 1
// 	intensity ..? この流れだと 0 <= intensity <= 1
// 	0 <= di <= 1 だし、 di = 1 - am - sp;
// 	return の因数が、全て 0 <= x <= 1 なら、 di = 1 - am - sp; だから、和が1 を超えることはない。
// 	*/
// 	// if (ref.d_di * light.d_intensity * cos_incident_and_vertical > 1)
// 	// 	return (1);
// 	return (ref.d_di * light.d_intensity * cos_incident_and_vertical);
// }

// // 鏡面反射光の放射強度Rs
// // Rs = Ks * Ii * cos^αθ
// // 	  = Ks * Ii * (VecV ・　VecR)^α

// // Ks: 鏡面反射係数（obj 依存）
// // Ii: 入射光の強度 (light 依存)
// // VecV は視野ベクトルの逆ベクトル	(ray と point)		方向ベクトル(正規化)
// // VecR は入射光の正反射ベクトル	(light と point)	方向ベクトル(正規化)
// // θ はVecV と VecR のなす角 (どうやって計算するんや？)
// // α は光沢度（obj 依存） 1 <= α
// // |VecV| = |VecR| = 1 (VecV と VecR は正規化する) Rs についてのでは、あくまで方向ベクトル
// // 

// // 二つの位置ベクトルにおいて、一点から一点に対するベクトルを取得する方法
// // BA = OA - OB
// // 感覚 向けたい方向(BA なら A) の位置ベクトル(OA) に対して、始点にしたいベクトル(OB)を指定する。


// // double	get_specular_ref(t_point_light light, t_sphere cir, t_vec3 intersection, t_ray eye)
// double	get_specular_ref(t_point_light light, t_intersection intersection, t_ray eye, t_reflect ref_info)
// {
// 	double	ref = 0;
// 	double	Ks = ref_info.d_sp;
// 	double	Ii = light.d_intensity;
// 	double	alpha = ref_info.sp_shininess;

// 	// t_vec3	inverse_eyedir = vec_normilize(vec_mult(eye.dir, -1));
// 	t_vec3	inverse_eyedir = vec_mult(eye.dir, -1);

// // vecR 1
// 	// t_vec3	vecR = vec_sub(light.pos, intersection);
// 	// vecR = vec_normilize(vecR);

// // vecR 2
// 	t_vec3	vertical = intersection.vertical_dir;
// 	// t_vec3	vecL = get_light_incident_dir(light, intersection);
// 	t_vec3	incident = vec_normilize(vec_sub(light.pos, intersection.position));
// 	t_vec3	regular_ref_incident = vec_sub( vec_mult(vertical, 2.0 * vec_dot(vertical, incident)), incident);

// 	double	inner_product = vec_dot(inverse_eyedir, regular_ref_incident);
// 	if (inner_product < 0)
// 		inner_product = 0;
// 	if (inner_product > 1)
// 		inner_product = 1;
// 	ref = Ks * Ii * pow(inner_product, alpha);
// 	return (ref);
// }

// // 半直線との交差判定の方法は　対象の形状ごとに異なる。
// // しかし、どの方法であっても、交差判定に結果として交点の位置や交点における法線方向がわかれば
// // 陰影の計算が可能である。
// double	get_ref2(t_intersection intersection, t_reflect ref_info, t_lightsource *light, t_ray eye)
// {
// 	double			ref;
// 	// t_img_color			ref;
// 	t_point_light	*point_light;
// 	// t_vec3	intersection;

// 	// intersection = get_ray_intersect_vec(eye, t);
// 	// eye.dir.x = 0;
// 	point_light = light->instance;
// 	ref = 0.0;
// 	// color_add(ref, get_ambient_ref2(ref_info, *point_light));
// 	// color_add(ref, get_deffsuse_ref2(intersection, ref_info, *point_light));
// 	// color_add(ref, get_specular_ref2(*point_light, intersection, eye, ref_info));
// 	ref += get_ambient_ref_double(ref_info, *point_light);
// 	// printf("%f, n", ref);
// 	ref += get_deffsuse_ref(intersection, ref_info, *point_light);
// 	// printf("%f, n", ref);
// 	ref += get_specular_ref(*point_light, intersection, eye, ref_info);
// 	// printf("%f, n", ref);
// 	if (ref > 1.0)
// 	{
// 		printf("ref is over 1   ref:%f", ref);
// 		print_vec(intersection.position, "intersection position");
// 		exit(1);
// 	}
// 	return (ref);
// }

// int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
// {
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

// 	t_intersection intersection;
// 	t_vec3		vec_win;
// 	t_img_color		color;
// 	double		ref;
// 	t_sphere	*instance;
// 	t_lightsource	*light = new_light(L_POINT, make_point_light_info(get_vec(-5, 5, -5), 1, gb_list), gb_list);

// 	t_obj	*sphere;
// 	// sphere = new_obj(O_SPHERE, make_sphere_instance(get_vec(0, 0, 5), 1, get_t_refrect(0, 1, 0, 0.0), gb_list), gb_list);
// 	sphere = new_obj(O_SPHERE, make_sphere_instance(get_vec(0, 0, 5), 1, get_t_refrect(0.01, 0.69, 0.3, 8), gb_list), gb_list);
// 	// sphere = new_obj(O_SPHERE, make_sphere_instance(get_vec(0, 0, 5), 1, get_t_refrect(0, 1, 0, 0.0), gb_list), gb_list);
// // get_t_refrect(0.1, 0.69, 0.3, 0.0), gb_list),
// // gb_list);

// 	int	x;
// 	int	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			vec_win = get_screen_vec(x, y, eye);
// 			eye.dir = vec_normilize(vec_sub(vec_win, eye.pos));
// 			intersection = sphere->get_intersection(eye, sphere);
// 			if (intersection.does_intersect == true)
// 			{
// 				// printf("%f %f %fn", intersection.position.x, intersection.position.y, intersection.position.z);
// 				instance = sphere->instance;
// 				ref = get_ref2(intersection, instance->ref, light, eye);
// 				mlx_put_to_img(img, x, y, make_white_color(ref * 255));
// 			}
// 			else
// 				mlx_put_to_img(img, x, y, BACK_COLOR);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (NULL);
// }

// // int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
// // {
// // 	t_intersection intersection;
// // 	t_vec3		vec_win;
// // 	t_img_color		color;
// // 	double		ref;
// // 	t_sphere	*instance;

// // 	t_lightsource	*light;
// // 	light = new_light(L_POINT, make_point_light_info(get_vec(-5, 5, -5), 
// // 		get_img_color(0, 255, 255, 255), gb_list), gb_list);

// // 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
// // 		&img->line_length, &img->endian);

// // 	t_obj	*sphere;
// // 	sphere = new_obj(O_SPHERE, 
// // 				make_sphere_instance( 
// // 					get_vec(0, 0, 5), 1, 
// // 					get_t_refrect(	get_img_color(0.1, 0.1, 0.1, 0.1), 
// // 									get_img_color(0.69, 0.69, 0.69, 0.69), 
// // 									get_img_color(0.3, 0.3, 0.3, 0.3), 
// // 									get_img_color(0.0, 0.0, 0.0, 0.0)), 
// // 									gb_list), 
// // 					gb_list);

// // 	eye.dir = get_vec(0, 0, 5);
// // 	int	x;
// // 	int	y = 0;
// // 	while (y < WIN_HEIGHT)
// // 	{
// // 		x = 0;
// // 		while (x < WIN_WIDTH)
// // 		{
// // 			vec_win = get_screen_vec(x, y, eye);
// // 			eye.dir = vec_normilize(vec_sub(vec_win, eye.pos));
// // 			intersection = sphere->get_intersection(eye, sphere);
// // 			if (intersection.does_intersect == true)
// // 			{
// // 				printf("%f %f %fn", intersection.position.x, intersection.position.y, intersection.position.z);
// // 				instance = sphere->instance;
// // 				ref = get_ref2(intersection, instance->ref, light, eye);
// // 				color.trgb.t = ref * 100;
// // 				color.trgb.r = ref * 100;
// // 				color.trgb.g = ref * 100;
// // 				color.trgb.b = ref * 100;
// // 				mlx_put_to_img(img, x, y, color.color);
// // 			}
// // 			else
// // 				mlx_put_to_img(img, x, y, BACK_COLOR);
// // 			x++;
// // 		}
// // 		y++;
// // 	}
// // 	return (NULL);
// // }
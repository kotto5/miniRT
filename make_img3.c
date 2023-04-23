#include "all.h"

// t_circle	*make_circle(t_vec3 origin, double r, t_dlist **gb_list)
// {
// 	t_circle	*circle;

// 	circle = ft_galloc(sizeof(t_circle), gb_list);
// 	if (!circle)
// 		return (NULL);
// 	circle->pos = origin;
// 	circle->r = r;
// 	circle->ref.am = 0.01;
// 	circle->ref.di = 0.69;
// 	// circle->ref.di = 1.00;
// 	circle->ref.sp = 0.3;
// 	circle->ref.sp_shininess = 8;
// 	circle->vertical = get_cir_vertical_dir;
// 	return (circle);
// }

// t_obj	*make_obj_circle(t_vec3 origin, double r, t_dlist **gb_list)
// {
// 	t_obj		*obj;
// 	t_circle	*circle;

// 	circle = ft_galloc(sizeof(t_circle), gb_list);
// 	if (circle == NULL)
// 		return (NULL);
// 	circle->pos = origin;
// 	circle->r = r;
// 	circle->ref.am = 0.01;
// 	circle->ref.di = 0.69;
// 	// circle->ref.di = 1.00;
// 	circle->ref.sp = 0.3;
// 	circle->ref.sp_shininess = 8;
// 	circle->vertical = get_cir_vertical_dir;
// 	obj = ft_galloc(sizeof(t_obj), gb_list);
// 	if (obj == NULL)
// 		return (NULL);
// 	obj->type = O_CIRCLE;
// 	obj->instance = circle;
// 	obj->get_intersection = get_circle_intersection;
// 	return (obj);
// }

// int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
// {
// 	t_obj	*circle;
// 	// void	*instance;

// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
// 		&img->line_length, &img->endian);
// 	// instance = make_circle(get_vec3(0, 0, 5), 1, gb_list);
// 	// if (!instance)
// 	// 	return (NULL);
// 	// circle = new_obj(O_CIRCLE, instance, gb_list);

// 	circle = make_obj_circle(get_vec(0, 0, 5), 1, gb_list);
// 	t_intersection inter;

// 	inter = circle->get_intersection(eye, circle);
// 	printf("%f, ", inter.distance);
// 	print_vec(inter.position, "position");
// 	print_vec(inter.vertical_dir, "vertical");

	
// 	return (NULL);
// }

t_color	get_ambient_ref2(t_reflect ref, t_point_light light)
{
	t_color	color;

	color.trgb.t = ref.am.trgb.t * light.intensity.trgb.t;
	color.trgb.r = ref.am.trgb.r * light.intensity.trgb.r;
	color.trgb.g = ref.am.trgb.g * light.intensity.trgb.g;
	color.trgb.b = ref.am.trgb.b * light.intensity.trgb.b;
	return (color);
}

t_color	get_deffsuse_ref2(t_intersection intersection, t_reflect ref, t_point_light light)
{
	double	cos;
	t_vec3	n;
	t_vec3	l;
	t_color	color;

	color.color = 0;
	n = intersection.vertical_dir;
	l = vec_normilize(vec_sub(light.pos, intersection.position));
	cos = vec_dot(n, l);
	if (cos < 0)
		return (color);
	color.trgb.t = light.intensity.trgb.t * ref.di.trgb.t * cos;
	color.trgb.r = light.intensity.trgb.r * ref.di.trgb.r * cos;
	color.trgb.g = light.intensity.trgb.g * ref.di.trgb.g * cos;
	color.trgb.b = light.intensity.trgb.b * ref.di.trgb.b * cos;
	return (color);
}

// t_color	get_specular_ref2(t_point_light light, t_circle cir, t_vec3 intersection, t_ray eye)
t_color	get_specular_ref2(t_point_light light, t_intersection intersection, t_ray eye, t_reflect ref_info)
{
	t_color	ref;

// 入射ベクトル ray と交点
	t_vec3	vecV = vec_normilize(vec_mult(eye.dir, -1));

// vecR
	t_vec3	vecN = intersection.vertical_dir;
	t_vec3	vecL = vec_normilize(vec_sub(light.pos, intersection.position));
	t_vec3	vecR = vec_sub( vec_mult(vecN, 2.0 * vec_dot(vecN, vecL)), vecL);

	double	inner_product = vec_dot(vecV, vecR);
	if (inner_product < 0)
		inner_product = 0;
	if (inner_product > 1)
		inner_product = 1;
	ref.trgb.t = light.intensity.trgb.t * pow(inner_product, ref_info.sp_shininess.trgb.t) * ref_info.sp.trgb.t;
	ref.trgb.r = light.intensity.trgb.r * pow(inner_product, ref_info.sp_shininess.trgb.r) * ref_info.sp.trgb.r;
	ref.trgb.g = light.intensity.trgb.g * pow(inner_product, ref_info.sp_shininess.trgb.g) * ref_info.sp.trgb.g;
	ref.trgb.b = light.intensity.trgb.b * pow(inner_product, ref_info.sp_shininess.trgb.b) * ref_info.sp.trgb.b;
	return (ref);
}

t_color	get_ref2(t_intersection intersection, t_reflect ref_info, t_lightsource *light)
{
	t_color			ref;
	t_point_light	*point;
	t_ray			eye;
	// t_vec3	intersection;

	// intersection = get_ray_intersect_vec(eye, t);
	eye.dir.x = 0;
	point = light->instance;
	ref.color = 0.0;
	color_add(ref, get_ambient_ref2(ref_info, *point));
	color_add(ref, get_deffsuse_ref2(intersection, ref_info, *point));
	color_add(ref, get_specular_ref2(*point, intersection, eye, ref_info));
	return (ref);
}

int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
{
	t_intersection intersection;
	t_vec3		vec_win;
	t_color		color;
	t_reflect	ref;

	t_lightsource	*light;
	light = new_light(L_POINT, make_point_light_info(get_vec(-5, -5, -5), \
		get_color(0, 255, 255, 255), gb_list), gb_list);

	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);

	t_obj	*circle;
	circle = new_obj(O_CIRCLE, \
				make_circle_instance( \
					get_vec(0, 0, 5), 1, \
					get_t_refrect(	get_color(0.1, 0.1, 0.1, 0.1), \
									get_color(0.69, 0.69, 0.69, 0.69), \
									get_color(0.3, 0.3, 0.3, 0.3), 
									get_color(0.0, 0.0, 0.0, 0.0)), 
									gb_list), \
					gb_list);

	eye.dir = get_vec(0, 0, 5);
	int	x;
	int	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = get_screen_vec(x, y, eye);
			eye.dir = vec_normilize(vec_sub(vec_win, eye.pos));
			intersection = circle->get_intersection(eye, circle);
			if (intersection.does_intersect == true)
			{
				color = get_ref2(intersection, )
				mlx_put_to_img(img, x, y, 0xffffff);
			}
			else
				mlx_put_to_img(img, x, y, BACK_COLOR);
			x++;
		}
		y++;
	}
	return (NULL);
}
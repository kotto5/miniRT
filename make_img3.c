#include "all.h"

t_circle	*make_circle(t_vec3 origin, double r, t_dlist **gb_list)
{
	t_circle	*circle;

	circle = ft_galloc(sizeof(t_circle), gb_list);
	if (!circle)
		return (NULL);
	circle->pos = origin;
	circle->r = r;
	circle->ref.am = 0.01;
	circle->ref.di = 0.69;
	// circle->ref.di = 1.00;
	circle->ref.sp = 0.3;
	circle->ref.sp_shininess = 8;
	circle->vertical = get_cir_vertical_dir;
	return (circle);
}

t_obj	*make_obj_circle(t_vec3 origin, double r, t_dlist **gb_list)
{
	t_obj		*obj;
	t_circle	*circle;

	circle = ft_galloc(sizeof(t_circle), gb_list);
	if (circle == NULL)
		return (NULL);
	circle->pos = origin;
	circle->r = r;
	circle->ref.am = 0.01;
	circle->ref.di = 0.69;
	// circle->ref.di = 1.00;
	circle->ref.sp = 0.3;
	circle->ref.sp_shininess = 8;
	circle->vertical = get_cir_vertical_dir;
	obj = ft_galloc(sizeof(t_obj), gb_list);
	if (obj == NULL)
		return (NULL);
	obj->type = O_CIRCLE;
	obj->instance = circle;
	obj->get_intersection = get_circle_intersection;
	return (obj);
}

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

double	get_ambient_ref2(double ref_am, t_light light)
{
	return (ref_am * light.intensity);
}

double	get_deffsuse_ref2(t_intersection intersection, t_reflect ref, t_light light)
{
	double	cos;
	t_vec3	n;
	t_vec3	l;

	n = intersection.vertical_dir;
	l = vec_normilize(vec_sub(light.pos, intersection.position));
	cos = vec_dot(n, l);
	if (cos < 0)
		return (0);
	return (ref.di * light.power * cos);
}

// double	get_specular_ref2(t_point_light light, t_circle cir, t_vec3 intersection, t_ray eye)
double	get_specular_ref2(t_point_light light, t_intersection intersection, t_ray eye, t_reflect ref_info)
{
	double	ref = 0;

// ref
	// double	Ks = cir.ref.sp;
	double	Ks = ref_info.sp;
	double	Ii = light.power;
	// double	alpha = cir.ref_info.sp_shininess;
	double	alpha = ref_info.sp_shininess;

// 入射ベクトル ray と交点
	// t_vec3	vecV = vec_mult(eye.dir, -1);
	t_vec3	vecV = vec_normilize(vec_mult(eye.dir, -1));

// vecR
	// t_vec3	vecN = get_cir_vertical_dir(cir, intersection.position);
	t_vec3	vecN = intersection.vertical_dir;
	// t_vec3	vecL = get_light_incident_dir(light, intersection.position);
	t_vec3	vecL = vec_normilize(vec_sub(light.pos, intersection.position));
	// t_vec3	vecR = vec_sub( vec_mult(vecN, 2.0 * vec_dot(vecN, vecL)), vecL);
	t_vec3	vecR = vec_sub( vec_mult(vecN, 2.0 * vec_dot(vecN, vecL)), vecL);

	double	inner_product = vec_dot(vecV, vecR);
	if (inner_product < 0)
		inner_product = 0;
	if (inner_product > 1)
		inner_product = 1;
	ref = Ks * Ii * pow(inner_product, alpha);
	return (ref);
}

double	get_ref2(t_intersection intersection, t_reflect ref, t_light light)
{
	double	ref;
	// t_vec3	intersection;

	// intersection = get_ray_intersect_vec(eye, t);
	ref = 0.0;
	ref += get_ambient_ref2(ref, light);
	ref += get_deffsuse_ref2(intersection, ref, light);
	ref += get_specular_ref(light, cir, intersection, eye);
	return (ref);
}



int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
{
	t_obj	*circle;
	t_intersection inter;
	t_vec3		vec_win;

	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	circle = make_obj_circle(get_vec(0, 0, 5), 1, gb_list);

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
			inter = circle->get_intersection(eye, circle);
			if (inter.does_intersect == true)
			{
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
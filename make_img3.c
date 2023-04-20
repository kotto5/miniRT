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
	return (NULL);
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


int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list)
{
	t_obj	*circle;
	t_intersection inter;
	// t_vec3		vec_win;

	(void)circle;
	(void)inter;
	(void)gb_list;
	// (void)img;
	(void)eye;

	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	circle = make_obj_circle(get_vec(0, 0, 5), 1, gb_list);

	// eye.dir = get_vec(0, 0, 5);
	// inter = circle->get_intersection(eye, circle);
	// printf("%f, ", inter.distance);
	// print_vec(inter.position, "position");
	// print_vec(inter.vertical_dir, "vertical");

	// int	x;
	// int	y = 0;
	// while (y < WIN_HEIGHT)
	// {
	// 	x = 0;
	// 	while (x < WIN_WIDTH)
	// 	{
	// 		vec_win = get_screen_vec(x, y, eye);
	// 		eye.dir = vec_normilize(vec_sub(vec_win, eye.pos));
	// 		inter = circle->get_intersection(eye, circle);
	// 		if (inter.does_intersect == true)
	// 		{
	// 			mlx_put_to_img(img, x, y, 0xffffff);
	// 		}
	// 		else
	// 			mlx_put_to_img(img, x, y, BACK_COLOR);
	// 		x++;
	// 	}
	// 	y++;
	// }

	return (NULL);
}
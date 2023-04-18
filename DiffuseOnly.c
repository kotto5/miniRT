#include "all.h"

// int	*make_img(t_img *img)
// {
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
// 			&img->line_length, &img->endian);
// 	t_ray		eye;
// 	t_circle	c1;
// 	double		t;
// 	t_vec3		vec_win;
// 	t_vec3		inter_p;
// 	t_point_light	p_light;
// 	t_color		color;
// 	p_light.power = 1;
// 	set_vec3(&p_light.pos, -5, 5, -5);
// 	set_vec3(&eye.pos, 0, 0, -5);
// 	// set_vec3(&eye.pos, 0, 0, 1);
// 	set_vec3(&c1.pos, 0, 0, 5);
// 	c1.r = 1.0;
// 	c1.ref.di = 1;

// 	int	x;
// 	int	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			vec_win = get_screen_vec(x, y);
// 			eye.dir = vec_sub(vec_win, eye.pos);
// 			eye.dir = vec_mult(eye.dir, 1.0 / vec_mag(eye.dir));

// 			t = get_ray_t_to_cir(eye, c1);
// 			if (t >= 0)
// 			{
// 				inter_p = get_ray_intersect_vec(eye, t);
// 				double	ref = get_deffsuse_ref(p_light, c1, inter_p);
// 				printf("ref: %f\n", ref);
// 				int	color_val = ref * 255;
// 				color.trgb.t = 0;
// 				color.trgb.r = color_val;
// 				color.trgb.g = color_val;
// 				color.trgb.b = color_val;
// 				// color.trgb.t = 0;
// 				// color.trgb.r = (255 - ref);
// 				// color.trgb.g = (255 - ref);
// 				// color.trgb.b = (255 - ref);
// 				mlx_put_to_img(img, x, y, color.color);
// 			}
// 			else
// 				mlx_put_to_img(img, x, y, 100 * 0x10000 + 149 * 0x100 + 237);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }


// int	*make_img(t_img *img)
// {
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
// 			&img->line_length, &img->endian);
// 	t_ray		eye;
// 	t_circle	c1;
// 	t_circle	c2;
// 	double		t;
// 	t_vec3		vec_win;
// 	t_vec3		inter_p;
// 	t_point_light	p_light;
// 	t_color		color;

// 	color.trgb.r = 10;
// 	color.trgb.g = 0;
// 	color.trgb.b = 255;
// 	color.trgb.t = 0;

// 	p_light.power = 1;
// 	set_vec3(&p_light.pos, -5, 5, -5);
// 	set_vec3(&eye.pos, 0, 0, -5);
// 	// set_vec3(&eye.pos, 0, 0, 1);
// 	set_vec3(&c1.pos, 0, 2, 5);
// 	set_vec3(&c2.pos, 0, -1, 5);
// 	c1.r = 1.0;
// 	c1.ref.di = 1;
// 	c2.r = 1.0;
// 	c2.ref.di = 1;

// 	int	x;
// 	int	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			vec_win = get_screen_vec(x, y);
// 			eye.dir = vec_sub(vec_win, eye.pos);
// 			eye.dir = vec_mult(eye.dir, 1.0 / vec_mag(eye.dir));

// 			t = get_ray_t_to_cir(eye, c1);
// 			if (t >= 0)
// 			{
// 				inter_p = get_ray_intersect_vec(eye, t);
// 				double	ref = get_deffsuse_ref(p_light, c1, inter_p);
// 				ref *= 255.0;
// 				mlx_put_to_img(img, x, y, ref * 0x000000ff);
// 				// mlx_put_to_img(img, x, y, ref * 0x0100000);
// 			}
// 			else
// 				mlx_put_to_img(img, x, y, 100 * 0x10000 + 149 * 0x100 + 237);

// 			t = get_ray_t_to_cir(eye, c2);
// 			if (t >= 0)
// 			{
// 				inter_p = get_ray_intersect_vec(eye, t);
// 				double	ref = get_deffsuse_ref(p_light, c2, inter_p);
// 				ref *= 255.0;
// 				mlx_put_to_img(img, x, y, ref * 0x000000ff);
// 				// mlx_put_to_img(img, x, y, ref * 0x0100000);
// 			}

// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }

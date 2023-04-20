/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleShading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:08:26 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/20 14:30:33 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	make_white_color(double bright)
{
	t_color	color;

	color.trgb.t = 0;
	color.trgb.r = bright;
	color.trgb.g = bright;
	color.trgb.b = bright;
	return (color.color);
}

t_circle	init_circle(t_vec3 origin, double r)
{
	t_circle	cir;

	cir.pos = origin;
	cir.r = r;
	cir.ref.am = 0.01;
	cir.ref.di = 0.69;
	// cir.ref.di = 1.00;
	cir.ref.sp = 0.3;
	cir.ref.sp_shininess = 8;
	cir.vertical = get_cir_vertical_dir;
	return (cir);
}


int	*make_img2(t_img *img, t_ray eye)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	t_circle	c1 = init_circle(get_vec(0, 0, 5) , 1);
	double		t;
	t_vec3		vec_win;
	t_point_light	p_light;
	p_light.power = 1;
	set_vec3(&p_light.pos, -5, 5, -5);
	// set_vec3(&p_light.pos, 5, -5, -4.9);
	set_vec3(&eye.pos, 0, 0, -5);
	set_vec3(&eye.dir, 0, 0, 1);
	t = get_ray_t_to_cir(eye, c1);
	printf("t %f \n", t);

	int	x;
	int	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = get_screen_vec(x, y, eye);
			eye.dir = vec_normilize(vec_sub(vec_win, eye.pos));
			t = get_ray_t_to_cir(eye, c1);
			if (t >= 0)
			{
				// inter_p = get_ray_intersect_vec(eye, t);
				// double	ref = get_deffsuse_ref(p_light, c1, inter_p);
				double	ref = get_ref(p_light, c1, eye, t);
				// printf("ref: %f\n", ref);
				mlx_put_to_img(img, x, y, make_white_color(ref * 255));
			}
			else
				mlx_put_to_img(img, x, y, 100 * 0x10000 + 149 * 0x100 + 237);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

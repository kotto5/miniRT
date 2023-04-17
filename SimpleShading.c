/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleShading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:08:26 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/17 22:41:32 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	make_white_color(t_color *color, double bright)
{
	color->trgb.t = 0;
	color->trgb.r = bright;
	color->trgb.g = bright;
	color->trgb.b = bright;
}

int	*make_img2(t_img *img, t_ray eye)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	t_circle	c1;
	double		t;
	t_vec3		vec_win;
	t_point_light	p_light;
	t_color		color;
	p_light.power = 1;
	set_vec3(&p_light.pos, -5, 5, -5);
	// set_vec3(&p_light.pos, 5, -5, -4.9);
	// set_vec3(&eye.pos, 0, 0, 1);
	set_vec3(&c1.pos, 0, 0, 5);
	c1.r = 1.0;
	c1.ref.di = 0.69;

	int	x;
	int	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = convert_vecter_to_window_from_imgvec(x, y, eye);
			eye.dir = vec_sub(vec_win, eye.pos);
			eye.dir = vec_mult(eye.dir, 1.0 / vec_mag(eye.dir));
			t = get_ray_t_to_cir(eye, c1);
			if (t >= 0)
			{
				// inter_p = get_intersect_point_ray_cir(eye, t);
				// double	ref = get_deffsuse_ref(p_light, c1, inter_p);
				double	ref = get_ref(p_light, c1, eye, t);
				printf("ref: %f\n", ref);
				make_white_color(&color, ref * 255);
				mlx_put_to_img(img, x, y, color.color);
			}
			else
				mlx_put_to_img(img, x, y, 100 * 0x10000 + 149 * 0x100 + 237);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

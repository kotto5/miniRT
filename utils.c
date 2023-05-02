/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/02 23:31:23 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	mlx_put_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vec3	get_screen_vec(int x, int y, t_ray eye)
{
	double	win_x;
	double	win_y;
	double	win_z;
	double	width;
	double	height;
	double	ord;

	width = (double)WIN_WIDTH;
	height = (double)WIN_HEIGHT;
	ord = (double)WIN_ORD;
	// win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x;
	// win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y;
	// win_z = eye.pos.z + eye.distance_to_window;
	// print_vec(eye.orientation, "win_x is");
	win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x + eye.orientation.x;
	win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y + eye.orientation.y;
	win_z = eye.pos.z + eye.distance_to_window + eye.orientation.z;
	return (get_vec(win_x, win_y, win_z));
}

double	get_distance_to_window(int fov)
{
	double			fov_rad;
	const double	pi = 3.14159265358979323846;

	fov_rad = (double)fov * pi / 180.0;
	return (((double)WIN_WIDTH / (double)WIN_ORD) / 2.0 / tan(fov_rad / 2.0));
}

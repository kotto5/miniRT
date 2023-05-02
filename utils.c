/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/02 22:50:49 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	mlx_put_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// t_vec3	get_screen_vec(int x, int y)
// {
// 	t_vec3	vec_win;

// 	// vec_win.x = (x / (WIN_WIDTH - 1.0)) - 1.0;
// 	// vec_win.y = (y / (WIN_HEIGHT - 1.0)) + 1.0;

// 	vec_win.x = (2.0 * x / (WIN_WIDTH - 1.0)) - 1.0;
// 	vec_win.y = (-2.0 * y / (WIN_HEIGHT - 1.0)) + 1.0;

// 	// vec_win.x = (4.0 * x / (WIN_WIDTH - 1.0)) - 2.0;
// 	// vec_win.y = (-4.0 * y / (WIN_HEIGHT - 1.0)) + 2.0;

// 	vec_win.z = 0;
// 	return (vec_win);
// }

// t_vec3	get_screen_vec(int x, int y, t_ray eye)
// {
// 	t_vec3	vec_win;

// 	vec_win.x = (2.0 * x / (WIN_WIDTH - 1.0)) - 1.0 + eye.pos.x;
// 	vec_win.y = (-2.0 * y / (WIN_HEIGHT - 1.0)) + 1.0 + eye.pos.y;
// 	vec_win.z = eye.pos.z + 5;
// 	return (vec_win);
// }

// static t_vec3	convert_to_vec(int x, int y, t_vec3 eye_pos)
t_vec3	get_screen_vec(int x, int y, t_ray eye)
{
	double	win_x;
	double	win_y;
	double	width;
	double	height;
	double	ord;

	width = (double)WIN_WIDTH;
	height = (double)WIN_HEIGHT;
	ord = (double)WIN_ORD;
	win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x;
	win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y;
	// return (get_vec(win_x, win_y, eye.pos.z + 5.0));
	return (get_vec(win_x, win_y, eye.pos.z + eye.distance_to_window));
}

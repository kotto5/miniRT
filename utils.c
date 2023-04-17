/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/17 16:42:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	mlx_put_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vec3	convert_vecter_to_window_from_imgvec(int x, int y)
{
	t_vec3	vec_win;

	// vec_win.x = (x / (WIN_WIDTH - 1.0)) - 1.0;
	// vec_win.y = (y / (WIN_HEIGHT - 1.0)) + 1.0;

	vec_win.x = (2.0 * x / (WIN_WIDTH - 1.0)) - 1.0;
	vec_win.y = (-2.0 * y / (WIN_HEIGHT - 1.0)) + 1.0;

	// vec_win.x = (4.0 * x / (WIN_WIDTH - 1.0)) - 2.0;
	// vec_win.y = (-4.0 * y / (WIN_HEIGHT - 1.0)) + 2.0;

	vec_win.z = 0;
	return (vec_win);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 19:05:31 by shtanemu          #+#    #+#             */
/*   Updated: 2023/04/28 02:37:46 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minirt.h"
#include "vector.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + \
			(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static bool	is_crossed(t_vec3 d, t_vec3 s, t_vec3 n)
{
	double	denom;

	denom = vec_dot(d, n);
	if (denom == 0.00)
		return (false);
	if (-1.0 * (vec_dot(s, n) / denom) > 0)
		return (true);
	else
		return (false);
}

static t_vec3	convert_to_vec(int x, int y, double eye_pos_z)
{
	double	xw;
	double	yw;

	xw = (2.0f * x) / ((double)WIN_WIDTH - 1.0f) - 1.0f;
	yw = (-2.0f * y) / ((double)WIN_HEIGHT - 1.0f) + 1.0f;
	return (get_vec(xw, yw, eye_pos_z));
}

int	put_plane(t_env *env)
{
	t_vec3	s;
	t_vec3	n;
	t_vec3	d;
	int		x;
	int		y;

	s = get_vec(0.0, 0.5, 0.0);
	n = get_vec(0.0, 1.5, 0.0);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			d = vec_normilize(vec_sub(convert_to_vec(x, y, 0.0), s));
			if (is_crossed(d, s, n))
				my_mlx_pixel_put(&env->img, x, y, 0x0000FF00);
			else
				my_mlx_pixel_put(&env->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	return (0);
}

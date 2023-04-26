/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ball.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:40:16 by shtanemu          #+#    #+#             */
/*   Updated: 2023/04/26 21:47:57 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "minirt.h"
#include "vector.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + \
			(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static bool	is_crossed(t_vec3 d, t_vec3 s, double r)
{
	double	a;
	double	b;
	double	root;
	double	t_1;
	double	t_2;

	a = vec_mag_sq(d);
	b = 2.0 * vec_dot(d, s);
	root = pow(b, 2.0) - (4.0 * a * (vec_mag_sq(s) - pow(r, 2)));
	if (a == 0)
		return (false);
	if (root < 0)
		return (false);
	t_1 = ((-1.0 * b) + sqrt(root)) / (2.0 * a);
	t_2 = ((-1.0 * b) - sqrt(root)) / (2.0 * a);
	if (t_1 > 0.0 || t_2 > 0.0)
		return (true);
	return (false);
}

static t_vec3	convert_to_vec(int x, int y, double eye_pos_z)
{
	double	win_x;
	double	win_y;
	double	width;
	double	height;
	double	ord;

	width = (double)WIN_WIDTH;
	height = (double)WIN_HEIGHT;
	ord = (double)WIN_ORD;
	win_x = (double)x / (ord / 2.0) - width / ord;
	win_y = height / ord - (double)y / (ord / 2.0);
	return (get_vec(win_x, win_y, eye_pos_z + 5.0));
}

int	put_ball(t_env *env)
{
	t_vec3	s;
	int		x;
	int		y;

	s = get_vec(0.0, 0.0, -5.0);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (is_crossed(\
					vec_normilize(\
						vec_sub(\
							convert_to_vec(x, y, s.z), s)), s, 0.5))
				my_mlx_pixel_put(&env->img, x, y, 0x0000FF00);
			else
				my_mlx_pixel_put(&env->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
	return (0);
}

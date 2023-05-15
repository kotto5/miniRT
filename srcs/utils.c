/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/15 10:08:42 by kakiba           ###   ########.fr       */
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

#include <sys/time.h>

static long	ft_get_time_in_usec(void)
{
	struct timeval	t1;
	long			sec_milli;
	long			s_time;

	if (gettimeofday(&t1, NULL))
	{
		return (-1);
	}
	s_time = (long)(t1.tv_sec);
	sec_milli = s_time * 10000000 + (long)(t1.tv_usec);
	// sec_milli = (long)(t1.tv_usec);
	// sec_milli = s_time * 1000 + (long)(t1.tv_usec) / 1000;
	return (sec_milli);
}

void	print_time(int a)
{
	static long	before;
	static long	now;

	now = ft_get_time_in_usec();
	if (before == 0)
		printf("[%d]time %d\n", a, 0);
	else
		printf("[%d]time %ld\n", a, now - before);
	before = now;
}

double	abs_double(double d)
{
	if (d < 0)
		return (d * -1.0);
	return (d);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/20 11:19:29 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	mlx_put_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_vec3	get_screen_vec(int x, int y, t_vec3 eye_position)
{
	double	win_x;
	double	win_y;
	double	win_z;
	double	width;
	double	height;

	width = (double)WIN_WIDTH;
	height = (double)WIN_HEIGHT;

	win_x = (eye_position.x - 1.0) + (2.0 * x / (width - 1.0));
	win_y = (eye_position.y - ASPECT) + (2.0 * y * ASPECT / (height - 1.0));
	win_z = eye_position.z + 1.0;

	// win_x = (eye_position.x - 1.0) + (2.0f * (double)x) / ((double)WIN_WIDTH - 1.0f) - 1.0f;
	// win_y = (eye_position.y - 1.0) + (-2.0f * (double)y) / ((double)WIN_HEIGHT - 1.0f) + 1.0f;
	// win_z = eye_position.z + 0.1;

	// win_z = eye.pos.z + eye.distance_to_window;
	// win_z = eye.pos.z + 0.466308;
	// win_z = eye.pos.z + 2.0;
	
	// printf("distance %f   eye z %f \n", eye.distance_to_window, eye.pos.z);
	return (get_vec(win_x, win_y, win_z));
}

	// win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x + eye.orientation.x;
	// win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y + eye.orientation.y;
	// win_z = eye.pos.z + eye.distance_to_window + eye.orientation.z;
	// win_y = eye.pos.y - (double)ASPECT + 2.0 * (double)ASPECT * y / height;

// t_vec3 get_screen_vec(int x, int y, t_ray eye)
// {
//     double win_x;
//     double win_y;
//     double win_z;
//     double width = (double)WIN_WIDTH;
//     double height = (double)WIN_HEIGHT;

//     // Normalize pixel coordinates to [-1, 1]
//     win_x = (2.0 * ((x + 0.5) / width) - 1.0);
//     win_y = (1.0 - 2.0 * ((y + 0.5) / height)) / ASPECT;

//     // Scale by distance to window
//     win_x = win_x * eye.distance_to_window;
//     win_y = win_y * eye.distance_to_window;
//     win_z = eye.pos.z + eye.distance_to_window;

//     return (get_vec(win_x, win_y, win_z));
// }

double	degree_to_radian(int degree)
{
	static const double	pi = 3.14159265358979323846;
	return ((double)degree * pi / 180.0);
}

double	get_distance_to_window(int fov)
{
	double			fov_rad;
	const double	pi = 3.14159265358979323846;

	fov_rad = (double)fov * pi / 180.0;
	return (1 / tan(fov_rad / 2.0));
	// return (((double)WIN_WIDTH / (double)WIN_ORD) / 2.0 / tan(fov_rad / 2.0));
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

// typedef struct	s_camera
// {
// 	double	higher_left_corner;
// 	double	horizontal;
// 	double	vertical;
// }				t_camera;

t_camera	*make_camera(double fov, t_vec3 pos, t_vec3 orientation)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	double	h = tan(degree_to_radian(fov) / 2.0);
	double	viewport_width = 2.0 * h;
	double	viewport_height = (double)ASPECT * viewport_width;
	double	focal_length = 1.0;

	camera->origin = pos;
	camera->orientation = vec_normilize(orientation);
	camera->rotation_axis = vec_normilize(vec_cross(camera->orientation, get_vec(0, 0, -1)));
	camera->rotation_radian = acos(vec_dot(camera->orientation, get_vec(0, 0, -1)));
	if (isnan(camera->rotation_axis.x) || isnan(camera->rotation_axis.y) ||
		isnan(camera->rotation_axis.z) || isnan(camera->rotation_radian))
	{
		printf("\x1b[41m ISNAN ! \x1b[41m\n");
		camera->rotation_axis = get_vec(0, 0, -1);
		camera->rotation_radian = 0;
	}
	camera->horizontal = get_vec(viewport_width, 0, 0);
	camera->vertical = get_vec(0, viewport_height, 0);
	camera->higher_left_corner = 
		vec_sub(vec_add(
			vec_sub(camera->origin, vec_mult(camera->horizontal, 0.5)),
				vec_mult(camera->vertical, 0.5)),
					get_vec(0, 0, focal_length));
	return (camera);
}

t_ray	*get_ray(t_camera *camera, int x, int y)
{
	static const double	fx = 1.0 / (double)(WIN_WIDTH - 1);
	static const double	fy = 1.0 / (double)(WIN_HEIGHT - 1);
	const double	u = (double)x * fx;
	const double	v = (double)y * fy;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ft_memset(ray, 0, sizeof(t_ray));
	ray->pos = camera->origin;
	ray->dir = vec_sub(vec_mult(camera->horizontal, u), vec_mult(camera->vertical, v));
	ray->dir = vec_add(ray->dir, camera->higher_left_corner);
	ray->dir = vec_sub(ray->dir, camera->origin);
	ray->dir = vec_normilize(ray->dir);
	return (ray);
}

void	exit_error(int ret)
{
	// printf("ERROR %d\n", ret);
	exit(ret);
}

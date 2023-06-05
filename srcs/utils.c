/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/01 15:12:31 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	mlx_put_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr \
		+ (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	get_distance_to_window(int fov)
{
	double			fov_rad;
	const double	pi = 3.14159265358979323846;

	fov_rad = (double)fov * pi / 180.0;
	return (1 / tan(fov_rad / 2.0));
}

t_camera	*make_camera(double fov, t_vec3 pos, t_vec3 forward)
{
	t_camera		*camera;
	const double	viewport_width = 2.0 * tan((double)fov * PI / 180.0 / 2.0);
	t_vec3			up;
	t_vec3			right;

	camera = malloc(sizeof(t_camera));
	if (camera == NULL)
		return (NULL);
	camera->orientation = vec_normalize(forward);
	if (fabs(camera->orientation.x) < EPS \
		&& fabs(camera->orientation.z) < EPS)
		up = (t_vec3){0.0, 0.0, 1.0};
	else
		up = (t_vec3){0.0, 1.0, 0.0};
	right = vec_normalize(vec_cross(up, camera->orientation));
	up = vec_cross(camera->orientation, right);
	camera->origin = pos;
	camera->horizontal = vec_mult(right, viewport_width);
	camera->vertical = vec_mult(up, (double)ASPECT * viewport_width);
	camera->higher_left_corner = vec_add(\
		vec_add(vec_sub(pos, vec_mult(camera->horizontal, 0.5)), \
		vec_mult(camera->vertical, 0.5)), \
		vec_mult(camera->orientation, FOCAL_LENGTH));
	camera->fov = fov;
	return (camera);
}

t_ray	*get_ray(t_camera *camera, int x, int y)
{
	static const double	fx = 1.0 / (double)(WIN_WIDTH - 1);
	static const double	fy = 1.0 / (double)(WIN_HEIGHT - 1);
	const double		u = (double)x * fx;
	const double		v = (double)y * fy;
	t_ray				*ray;

	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ft_memset(ray, 0, sizeof(t_ray));
	ray->pos = camera->origin;
	ray->dir = vec_sub(vec_sub(\
		vec_add(camera->higher_left_corner, \
		vec_mult(camera->horizontal, u)), \
		vec_mult(camera->vertical, v)), ray->pos);
	ray->dir = vec_normalize(ray->dir);
	return (ray);
}

void	exit_error(int ret)
{
	printf("ERROR %d\n", ret);
	exit(ret);
}

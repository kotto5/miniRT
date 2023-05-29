/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/29 15:56:40 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	mlx_put_to_img(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double    degree_to_radian(int degree)
{
    static const double    pi = 3.14159265358979323846;
    return ((double)degree * pi / 180.0);
}

// t_vec3	get_screen_vec(int x, int y, t_vec3 eye_position)
// {
// 	double	win_x;
// 	double	win_y;
// 	double	win_z;
// 	double	width;
// 	double	height;
// 	double	ord;

// 	width = (double)WIN_WIDTH;
// 	height = (double)WIN_HEIGHT;
// 	ord = (double)WIN_ORD;
// 	win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x;
// 	win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y;
// 	win_z = eye.pos.z + eye.distance_to_window;
// 	print_vec(eye.orientation, "win_x is");
// 	win_x = (double)x / (ord / 2.0) - width / ord + eye.pos.x + eye.orientation.x;
// 	win_y = height / ord - (double)y / (ord / 2.0) + eye.pos.y + eye.orientation.y;
// 	win_z = eye.pos.z + eye.distance_to_window + eye.orientation.z;
// 	return (get_vec(win_x, win_y, win_z));
// }


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

int	get_rotate_axis(t_vec3 base_vec, t_vec3 orien_vec, t_vec3 *rotate_axis, double *rotate_angle)
{
	*rotate_axis = vec_normalize(vec_cross(orien_vec, base_vec));
	// if (vec_mag(*rotate_axis) <= 0)
	if (isnan(rotate_axis->x) || isnan(rotate_axis->y) || isnan(rotate_axis->z))
	{
		printf("====%s get_rotate_axis PLOBLEM ! %s====\n", BACK_COLOR_RED, BACK_COLOR_DEF);
		if (vec_dot(base_vec, orien_vec) > 0)
		{
			printf("====%s in IF %s====\n", BACK_COLOR_RED, BACK_COLOR_DEF);
		// A and B are in the same direction.
		// Any axis of rotation is valid. We choose (1, 0, 0).
			*rotate_axis = get_vec(1.0, 0.0, 0.0);
			*rotate_angle = M_PI;  // 180 degree rotation
		}
		else
		{
			printf("====%s in ELSE %s====\n", BACK_COLOR_RED, BACK_COLOR_DEF);
			*rotate_axis = get_vec(1.0, 0.0, 0.0);
			*rotate_angle = 0.0;  // No rotation needed
			// A and B are in opposite directions.
			// Any axis perpendicular to A (and B) is valid. We choose (1, 0, 0) if A is not along x, and (0, 1, 0) otherwise.
		}
	}
	else
	{
		*rotate_axis = vec_normalize(*rotate_axis);
		*rotate_axis = vec_mult(*rotate_axis, 1);
		*rotate_angle = (acos(vec_dot(base_vec, orien_vec) / (vec_mag(base_vec) * vec_mag(orien_vec))));
	}
	return (SUCCESS);
}

// t_camera	*make_camera(double fov, t_vec3 pos, t_vec3 orientation)
// {
// 	t_camera	*camera;

// 	camera = malloc(sizeof(t_camera));
// 	if (camera == NULL)
// 		return (NULL);
// 	double	h = tan(degree_to_radian(fov) / 2.0);
// 	double	viewport_width = 2.0 * h;
// 	double	viewport_height = (double)ASPECT * viewport_width;
// 	double	focal_length = 1.0;

// 	camera->origin = pos;
// 	camera->orientation = vec_normalize(orientation);
// 	// camera->rotation_axis = vec_normalize(vec_cross(camera->orientation, get_vec(0, 0, -1)));
// 	// camera->rotation_radian = acos(vec_dot(camera->orientation, get_vec(0, 0, -1)));
// 	get_rotate_axis(get_vec(0, 0, 1), orientation, &camera->rotation_axis, &camera->rotation_radian);
// 	if (isnan(camera->rotation_axis.x) || isnan(camera->rotation_axis.y) ||
// 		isnan(camera->rotation_axis.z) || isnan(camera->rotation_radian))
// 	{
// 		printf("====%s ISNAN ! %s====\n", BACK_COLOR_RED, BACK_COLOR_DEF);
// 		camera->rotation_axis = get_vec(0, 0, 1);
// 		camera->rotation_radian = 0;
// 	}
// 	camera->horizontal = get_vec(viewport_width, 0, 0);
// 	camera->vertical = get_vec(0, viewport_height, 0);
// 	camera->higher_left_corner = 
// 		vec_sub(vec_add(
// 			vec_sub(camera->origin, vec_mult(camera->horizontal, 0.5)),
// 				vec_mult(camera->vertical, 0.5)),
// 					get_vec(0, 0, focal_length));
// 	return (camera);
// }

t_camera	*make_camera(double fov, t_vec3 pos, t_vec3 forward)
{
    t_camera	*camera;
    
    camera = malloc(sizeof(t_camera));
    if (camera == NULL)
        return (NULL);

    // compute the viewport size
    double	h = tan(degree_to_radian(fov) / 2.0);
    double	viewport_width = 2.0 * h;
    double	viewport_height = (double)ASPECT * viewport_width;
    double	focal_length = 1.0;

    // normalize the forward vector
    camera->orientation = vec_normalize(forward);

    // choose an up vector
    t_vec3 up;
    if (fabs(camera->orientation.x) < EPS && fabs(camera->orientation.z) < EPS) { // if the camera->orientation is almost (0, ±1, 0)
        up = (t_vec3){0.0, 0.0, 1.0};  // choose a different up vector
    } else {
        up = (t_vec3){0.0, 1.0, 0.0};  // default up vector
    }
    // compute the right and true up vectors
    // t_vec3 right = vec_normalize(vec_cross(camera->orientation, up));
    t_vec3 right = vec_normalize(vec_cross(up, camera->orientation));
    up = vec_cross(camera->orientation, right);
    // up = vec_cross(right, camera->orientation);



	// right = vec_mult(right, -1);
	// up = vec_mult(up, -1);

    // compute the corners of the viewport

    t_vec3 horizontal = vec_mult(right, viewport_width);
    t_vec3 vertical = vec_mult(up, viewport_height);
    t_vec3 middle = vec_mult(camera->orientation, focal_length);
    t_vec3 higher_left_corner = vec_add(vec_add(vec_sub(pos, vec_mult(horizontal, 0.5)), vec_mult(vertical, 0.5)), middle);

    // store the results
    camera->origin = pos;
    camera->horizontal = horizontal;
    camera->vertical = vertical;
    camera->higher_left_corner = higher_left_corner;
	camera->fov = fov;

    return camera;
}

t_ray	*get_ray(t_camera *camera, int x, int y)
{
	static const double	fx = 1.0 / (double)(WIN_WIDTH - 1);
	static const double	fy = 1.0 / (double)(WIN_HEIGHT - 1);
	const double	u = (double)x * fx;
	const double	v = (double)y * fy;
	t_ray	*ray;
	t_vec3	screen_pos;

	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ft_memset(ray, 0, sizeof(t_ray));
	screen_pos = vec_sub(
		vec_add(camera->higher_left_corner, vec_mult(camera->horizontal, u)),
		vec_mult(camera->vertical, v));
	ray->pos = camera->origin;
	ray->dir = vec_sub(screen_pos, ray->pos);
	ray->dir = vec_normalize(ray->dir);
	return (ray);
}

void	exit_error(int ret)
{
	// printf("ERROR %d\n", ret);
	exit(ret);
}

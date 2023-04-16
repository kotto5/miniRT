#include "all.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

bool	do_intersect_ray_and_square(t_ray ray, t_square sq)
{
	double	t = vec_dot(sq.n_dir, vec_sub(sq.pos, ray.pos)) / 
		vec_dot(ray.dir, sq.n_dir);

	if (t >= 0)
		return (1);
	else
		return (0);
}

// A = |VecRayDir|^2
// B = 2 * (VecRayDir . (VecRayP - VecCirP))
// C = (VecRayP - VecCirP)^2 - r^2
// 交差している座標 p = VecRayP + t*VecRayDir
double	get_ray_t_to_cir(t_ray ray, t_circle cir)
{
	double	A = vec_mag_sq(ray.dir);
	double	B = 2 * vec_dot(ray.dir, vec_sub(ray.pos, cir.pos));
	double	C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
	double	root = B * B - (4.0 * A * C);
	if (root < 0)
		return (-1);
	else
		root = sqrt(root);
	double	t = (-1.0 * B) - (root / 2.0 / A);
	return (t);
}

t_vec3	get_intersect_point_ray_cir(t_ray ray, double t)
{
	return (vec_add(ray.pos, vec_mult(ray.dir, t)));
}

t_vec3	get_normal_cir(t_circle cir, t_vec3 surface_p)
{
	t_vec3	n_prime;

	n_prime = vec_sub(surface_p, cir.pos);
	return (vec_mult(n_prime, 1.0 / vec_mag(n_prime)));
}

t_vec3	convert_vecter_to_window_from_imgvec(int x, int y)
{
	t_vec3	vec_win;

	vec_win.x = (2.0 * x / (WIN_WIDTH - 1.0)) - 1.0;
	vec_win.y = (-2.0 * y / (WIN_HEIGHT - 1.0)) + 1.0;
	vec_win.z = 0;
	return (vec_win);
}


int	*make_img(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	t_vec3		vec_win;
	t_ray		eye;
	t_circle	c1;
	double		t;
	t_vec3		n;
	t_vec3		inter_p;

	set_vec3(&c1.pos, 0, 0, 5);
	c1.r = 1.0;
	set_vec3(&eye.pos, 0, 0, -5);
	int	x;
	int	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = convert_vecter_to_window_from_imgvec(x, y);
			// printf("%f, %f, %f\n", vec_win.x, vec_win.y, vec_win.z);
			eye.dir = vec_sub(vec_win, eye.pos);
			t = get_ray_t_to_cir(eye, c1);
			if (t >= 0)
			{
				inter_p = get_intersect_point_ray_cir(eye, t);
				n = get_normal_cir(c1, inter_p);
				my_mlx_pixel_put(img, x, y, 0xcca0fff0);
			}
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

#include "all.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// 視点位置
// 画像の二次元座標→空間の三次元変換
// 画像の座標 Xs, Ys から 三次元座標 Xw Yw Zw への変換
// Xw = 2Xs / (WIDTH-1) - 1.0
// Yw = 2Ys / (HEIGHT-1) - 1.0
// Zw = 0

// vec3 = vec1 + vec2
t_vec3	vec_add(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.x + vb.x;
	ans.y = va.y + vb.y;
	ans.z = va.z + vb.z;
	return (ans);
}

// void	vec_sub(t_vec3 va, t_vec3 vb, t_vec3 *ans)
// {
// 	ans->x = va.x - vb.x;
// 	ans->y = va.y - vb.y;
// 	ans->z = va.z - vb.z;
// }

// vec3 = vec1 - vec2
t_vec3	vec_sub(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.x - vb.x;
	ans.y = va.y - vb.y;
	ans.z = va.z - vb.z;
	return (ans);
}

// vec3 = k * vec1
t_vec3	vec_mult(t_vec3 va, double k)
{
	t_vec3	ans;

	ans.x = va.x * k;
	ans.y = va.y * k;
	ans.z = va.z * k;
	return (ans);
}

// vec3 = vec1 ・ vec2
double	vec_dot(t_vec3 va, t_vec3 vb)
{
	return ((va.x * vb.x) + (va.y * vb.y) + (va.z * vb.z));
}

// vec3 = vec1 × vec2
t_vec3	vec_cross(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.y * vb.z - va.z * vb.y;
	ans.y = va.z * vb.x - va.x * vb.z;
	ans.z = va.x * vb.y - va.y * vb.x;
	return (ans);
}

// ret = |vec1| * |vec1|
double	vec_mag_sq(t_vec3 va)
{
	return (va.x * va.x + va.y * va.y + va.z * va.z);
}

// ret = |vec1|
double	vec_mag(t_vec3 va)
{
	return (sqrt(vec_mag_sq(va)));
}


void	set_vec3(t_vec3 *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

// bool	do_intersect_ray_and_object(t_ray ray, t_circle cir)
// {
// 	double	A = vec_mag_sq(ray.dir);
// 	double	B = 2 * vec_dot(ray.pos, ray.dir);
// 	double	C = vec_mag_sq(ray.pos) - (cir.r * cir.r);
// 	double	root = sqrt(B * B - (4 * A * C));
// 	double	t;
// 	if (root >= 0)
// 		t = (-1 * B) + (root / 2 / A);
// 	else
// 		t = (-1 * B) - (root / 2 / A);
// 	if (t > 0)
// 		return (1);
// 	else if (t == 0)
// 		return (1);
// 	else
// 		return (0);
// }

bool	do_intersect_ray_and_object(t_ray ray, t_circle cir)
{
	double	A = vec_mag_sq(ray.dir);
	double	B = 2 * vec_dot(ray.dir, vec_sub(ray.pos, cir.pos));
	double	C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
	double	root = B * B - (4.0 * A * C);
	if (root < 0)
		return (0);
	else
		root = sqrt(root);
	double	t = (-1.0 * B) - (root / 2.0 / A);
	if (t >= 0)
		return (1);
	else
		return (0);
}

// bool do_intersect_ray_and_object(t_ray ray, t_circle cir)
// {
// 	double A = vec_mag_sq(ray.dir);
// 	double B = 2.0 * vec_dot(ray.dir, vec_sub(ray.pos, cir.pos));
// 	double C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
// 	double discriminant = B * B - (4.0 * A * C);

// 	if (discriminant < 0)
// 		return 0;
// 	double root1 = (-1.0 * B + sqrt(discriminant)) / (2.0 * A);
// 	double root2 = (-1.0 * B - sqrt(discriminant)) / (2.0 * A);
// 	double t = (root1 > 0 && (root1 < root2 || root2 <= 0)) ? root1 : root2;
// 	return (t > 0);
// }

t_vec3	convert_vecter_to_window_from_imgvec(int x, int y)
{
	t_vec3	vec_win;

	vec_win.x = (2.0 * x / (WIN_WIDTH - 1.0)) - 1.0;
	vec_win.y = (-2.0 * y / (WIN_HEIGHT - 1.0)) + 1.0;
	// vec_win.x = (2.0 * x / (WIN_WIDTH - 1.0));
	// vec_win.y = (2.0 * y / (WIN_HEIGHT + 1.0));
	// vec_win.x = (2.0 * x / (WIN_WIDTH)) - 1.0;
	// vec_win.y = (2.0 * y / (WIN_HEIGHT)) + 1.0;
	vec_win.z = 0;
	return (vec_win);
}

int	*make_img(t_img *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

	t_vec3		vec_win;
	t_ray		eye;
	t_circle	c1;
	t_circle	c2;

	set_vec3(&c1.pos, 0, 0, 5);
	set_vec3(&c2.pos, 1, 1, 5);
	// set_vec3(&c1.pos, 2, 2, 5);
	c1.r = 1.0;
	c2.r = 1.0;
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
			if (do_intersect_ray_and_object(eye, c1) && do_intersect_ray_and_object(eye, c2))
				my_mlx_pixel_put(img, x, y, 0xc0ff00);
			else if (do_intersect_ray_and_object(eye, c1) || do_intersect_ray_and_object(eye, c2))
				my_mlx_pixel_put(img, x, y, 0x00ff00);
			else
				my_mlx_pixel_put(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}


// {
// 		t_vec3		v1 = {3, 4, 5};
// 	t_vec3		v2 = {6, 7, 8};
// 	t_vec3		v3 = {9, 10, 11};
// 	t_vec3		vbuf;
// 	printf("%f, %f, %f\n", v1.x, v1.y, v1.z);
// 	printf("%f, %f, %f\n", v2.x, v2.y, v2.z);
// 	printf("%f, %f, %f\n", v3.x, v3.y, v3.z);
// 	vbuf = vec_add(v1, v2);
// 	printf("%f, %f, %f\n", vbuf.x, vbuf.y, vbuf.z);
// 	vbuf = vec_add(vec_mult(v1, 3), vec_mult(v2, 4));
// 	printf("%f, %f, %f\n", vbuf.x, vbuf.y, vbuf.z);
// 	v1 = v3;
// 	printf("%f, %f, %f\n", v1.x, v1.y, v1.z);
// 	v1.y = 0;
// 	printf("%f, %f, %f\n", v1.x, v1.y, v1.z);
// 	vbuf = vec_add(vec_sub(vec_mult(v1, 2), vec_mult(v2, 5)), vec_mult(v3, 10));
// 	printf("%f, %f, %f\n", vbuf.x, vbuf.y, vbuf.z);
// 	double	buf;
// 	buf = vec_dot(v2, v3);
// 	printf("%f\n", buf);
// 	vbuf = vec_cross(v2, v3);
// 	printf("%f, %f, %f\n", vbuf.x, vbuf.y, vbuf.z);
// }

// gradation!!
// int	*make_img(t_img *img)
// {
// 	t_color	color;
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
// 	printf("%x \n", color.color);
// 	int	x;
// 	int	y = 0;

// 	color.trgb.t = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		color.trgb.g = (unsigned char)y;
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			color.trgb.r = 255 - (unsigned char)x;
// 			color.trgb.b = (unsigned char)(x * y / 255);
// 			my_mlx_pixel_put(img, x, y, color.color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }

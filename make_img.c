#include "all.h"


// int	*make_img(t_img *img)
// {
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
// 			&img->line_length, &img->endian);
// 	t_vec3		vec_win;
// 	t_ray		eye;
// 	t_circle	c1;
// 	double		t;
// 	t_vec3		n;
// 	t_vec3		inter_p;
// 	t_point_light	p_light;
// 	set_vec3(&p_light.pos, -5, 5, -5);

// 	set_vec3(&c1.pos, 0, 0, 5);
// 	c1.r = 1.0;
// 	set_vec3(&eye.pos, 0, 0, -5);
// 	int	x;
// 	int	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			vec_win = convert_vecter_to_window_from_imgvec(x, y);
// 			// printf("%f, %f, %f\n", vec_win.x, vec_win.y, vec_win.z);
// 			eye.dir = vec_sub(vec_win, eye.pos);
// 			t = get_ray_t_to_cir(eye, c1);
// 			if (t >= 0)
// 			{
// 				inter_p = get_intersect_point_ray_cir(eye, t);
// 				n = get_normal_cir(c1, inter_p);
// 				mlx_put_to_img(img, x, y, 0xcca0fff0);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }

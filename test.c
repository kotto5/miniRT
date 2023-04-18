
// int	*make_img(t_img *img)
// {
// 	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

// 	t_vec3		vec_win;
// 	t_ray		eye;
// 	t_circle	c1;
// 	double		t;
// 	// t_circle	c2;

// 	set_vec3(&c1.pos, 0, 0, 5);
// 	// set_vec3(&c2.pos, 1, 1, 5);
// 	// set_vec3(&c1.pos, 2, 2, 5);
// 	c1.r = 1.0;
// 	// c2.r = 1.0;
// 	set_vec3(&eye.pos, 0, 0, -5);
// 	int	x;
// 	int	y = 0;
// 	while (y < WIN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIN_WIDTH)
// 		{
// 			vec_win = get_screen_vec(x, y);
// 			// printf("%f, %f, %f\n", vec_win.x, vec_win.y, vec_win.z);
// 			eye.dir = vec_sub(vec_win, eye.pos);
// 			t = get_ray_t_to_cir(eye, c1);
// 			if (t >= 0)
// 			{
// 				mlx_put_to_img(img, x, y, 0xcca0fff0);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }


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
// 			mlx_put_to_img(img, x, y, color.color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (SUCCESS);
// }

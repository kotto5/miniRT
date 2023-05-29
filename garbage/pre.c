
// bool    is_crossed(t_vec3 d, t_vec3 s, double r)
// {
//     double    a;
//     double    b;
//     double    root;
//     double    t_1;
//     double    t_2;

//     a = vec_mag_sq(d);
//     b = 2.0 * vec_dot(d, s);
//     root = pow(b, 2.0) - (4.0 * a * (vec_mag_sq(s) - pow(r, 2)));
//     if (a == 0.0f)
//         return (false);
//     if (root < 0.0f)
//         return (false);
//     t_1 = ((-1.0 * b) + sqrt(root)) / (2.0 * a);
//     t_2 = ((-1.0 * b) - sqrt(root)) / (2.0 * a);
//     if (t_1 > 0.0 || t_2 > 0.0)
//         return (true);
//     return (false);
// }

// // 視点の移動
// // ウィンドウの大きさ変換
// // fov の変換
// // 視線方向の回転

// t_vec3    convert_to_vec(int x, int y, t_vec3 pos)
// {
//     double   	win_x;
//     double   	win_y;
//     double 		width = (double)WIN_WIDTH;
//     double 		height = (double)WIN_HEIGHT;
// 	// double		w = 1;
// 	// double		degree = 90;

// 	// double			fov_rad;
// 	// const double	pi = 3.14159265358979323846;
// 	// fov_rad = degree * pi / 180.0;
// 	// w = tan(fov_rad / 2.0);

// 	// double		screen_width = 2 * w;
// 	// double		screen_height = screen_width * ASPECT;
//     // win_x = ((screen_width * (double)x) / (width - 1.0f) - screen_width / 2.0) + pos.x;
//     // win_y = ((screen_height * (double)y) / (height - 1.0f) - screen_height / 2.0) + pos.y;

//     win_x =      (2.0f * x) / (width - 1.0f)          - 1.0 + pos.x;
//     win_y = (-2.0f * y) / (height - 1.0f) + 1.0f + pos.y;

//     // win_y = ((-2.0f *  ASPECT * y) / (height - 1.0f) + 1.0f + pos.y);
//     // win_x *= fov;
//     // win_y *= fov;
//     // dprintf(2, "win x: %f\n", win_x);
//     // dprintf(2, "win y: %f\n", win_y);
//     return (get_vec(win_x, win_y, pos.z + 1));
// }

/*
#define RADIUS 1

int	*color_img(t_env *env)
{
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &env->img.endian);

	t_vec3			screen_pos;

	// t_intersection	intersection;
	t_obj			*obj;
	obj = new_obj(O_SPHERE, get_t_refrect(b_color_get(0, 0.1, 0.1, 0.1), b_color_get(0.0, 0.0, 0.69, 0.69), b_color_get(0, 0.30, 0.30, 0.30), 5, false, (t_bright_color){0.5, 0.5, 0.5, 0.5}),
		make_sphere_instance(get_vec(0, 0, 0), RADIUS));

	int	x = 0;
	int	y = 0;

	env->eye = malloc(sizeof(t_ray));
	// env->eye->pos = get_vec(1.0, 0, -5);
	// env->eye->pos = get_vec(2, 0, -5);
	// env->eye->pos = get_vec(3, 0, -5);
	env->eye->pos = get_vec(4, 0, -5);
	// env->eye->pos = get_vec(2, 0, -10);
	// env->eye->pos = get_vec(60, 0, -300);


	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			screen_pos = convert_to_vec(x, y, env->eye->pos);
			env->eye->dir = vec_sub(screen_pos, env->eye->pos);
			env->eye->dir = vec_normalize(env->eye->dir);
			// env->eye = get_ray(env->camera, x, y);

			// intersection = obj->get_intersection(*env->eye, obj);
			// if (intersection.does_intersect)
			// 	mlx_put_to_img(&env->img, x, y, 0xFF);
			// else
			// 	mlx_put_to_img(&env->img, x, y, 0x0);

			if (is_crossed(env->eye->dir, env->eye->pos, RADIUS))
				mlx_put_to_img(&env->img, x, y, 0xFF);
			else
				mlx_put_to_img(&env->img, x, y, 0x0);
			x++;
		}
		y++;
	}
	print_time(4);
	return (NULL);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/02 22:51:00 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	do_nothing(void *ptr){
	(void)ptr;
	return ;
}

void	ft_exit(int status, t_dlist **gc)
{
	ft_dlstclear(gc, free);
	exit(status);
}

int	*make_img6(t_env *env);

int	key_event(int key, void *data)
{
	t_env	*env = data;

	if (key == ALLOW_DOWN)
		env->eye.pos.y += 0.1;
	else if (key == ALLOW_UP)
		env->eye.pos.y -= 0.1;
	else if (key == ALLOW_LEFT)
		env->eye.pos.x += 0.1;
	else if (key == ALLOW_RIGHT)
		env->eye.pos.x -= 0.1;
	else if (key == KEY_Z)
		env->eye.pos.z += 0.1;
	else if (key == KEY_X)
		env->eye.pos.z -= 0.1;
	else if (key == 53)
		ft_exit(0, &env->gb_list);
	else
	{
		printf("key is :%d\n", key);
		return (0);
	}
	// make_img6(&env->img, env->eye, &env->gb_list);
	make_img6(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}

double	get_distance_to_window(int fov)
{
	double			fov_rad;
	const double	pi = 3.14159265358979323846;

	fov_rad = (double)fov * pi / 180.0;
	return (((double)WIN_WIDTH / (double)WIN_ORD) / 2.0 / tan(fov_rad / 2.0));
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_env	env;
	env.gb_list = NULL;

	// set_vec3(&env.eye.pos, 3, 2, -1);
	set_vec3(&env.eye.pos, 3, 0, -5);
	// env.eye.distance_to_window = get_distance_to_window(50);
	// env.eye.distance_to_window = get_distance_to_window(70);
	// env.eye.distance_to_window = get_distance_to_window(100);
	env.eye.distance_to_window = get_distance_to_window(160);
	// env.eye.distance_to_window = get_distance_to_window(40);
	printf("distance_to_window is %f\n", env.eye.distance_to_window);
	// set_vec3(&env.eye.pos, 0.0, 0, -5);
	// set_vec3(&env.eye.pos, -0.25, 0.5, 1);
	// set_vec3(&env.eye.pos, 5, 2, 0);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	// set_event();
	mlx_key_hook(env.win, key_event, &env);
	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
	make_img6(&env);
	// ft_dlstclear(&gb_list, free);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	printf("PUT IMAGE TO WINDOW\n");
	mlx_loop(env.mlx);
}


// int	main()
// {
// 	t_img_color	color;
// 	char	*str;

// 	str = "31tokyo";

// 	printf("%p\n", &color.color);
// 	printf("%p\n", &color.trgb);
// 	printf("%p\n", &color.trgb.t);
// 	printf("%p\n", &color.trgb.r);
// 	printf("%p\n", &color.trgb.g);
// 	printf("%p\n", &color.trgb.b);
	
// 	color.trgb.t = 0xfa;
// 	color.trgb.r = 0x10;
// 	color.trgb.g = 0x20;
// 	color.trgb.b = 0x30;
// 	printf("%x\n", color.color);
// 	printf("%x\n", color.trgb.t);
// 	printf("%x\n", color.trgb.r);
// 	printf("%x\n", color.trgb.g);
// 	printf("%x\n", color.trgb.b);

// 	printf("%p\n", str);
// 	printf("%p\n", str + 1);
// }

__attribute__((destructor)) static void destructor()
{
	system("leaks -q miniRT");
}

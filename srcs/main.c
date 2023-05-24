/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/24 14:49:41 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	initialize_env(t_env *env)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return (ERROR);
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	if (env->win == NULL)
		return (ERROR);
	env->img.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (env->img.img == NULL)
		return (ERROR);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &env->img.endian);
	set_event(env);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 2)
		exit_error(1);
	printf("EPS %f\n", EPS);
	ft_memset(&env, 0, sizeof(t_env));
	if (parse_file(&env, argv[1]) == ERROR)
		exit_error(1);
	if (initialize_env(&env) == ERROR)
		exit_error(2);
	if (color_img(&env) == ERROR)
		exit_error(3);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	printf("PUT IMAGE TO WINDOW\n");
	mlx_loop(env.mlx);
	// gc_clear();
	// printf("SUCSESS!\n");
	return (0);
}

// 全体で2000ms くらい
// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	(void)argv;
// 	t_env	env;

// 	env.gb_list = NULL;
// 	set_vec3(&env.eye.pos, 0, 0, -5);
// 	set_vec3(&env.eye.orientation, 0,0,1);
// 	env.eye.distance_to_window = get_distance_to_window(90);
// 	printf("distance_to_window is %f\n", env.eye.distance_to_window);

// 	env.obj_list = get_obj_list(&env.gb_list);
// 	env.light_list = get_light_list(&env.gb_list);
// 	// env.obj_tree = get_obj_tree(&env);

// 	env.mlx = mlx_init();
// 	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
// 	set_event(&env);
// 	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
// 	color_img(&env);
// 	// ft_dlstclear(&gb_list, free);
// 	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
// 	printf("PUT IMAGE TO WINDOW\n");
// 	mlx_loop(env.mlx);
// }

// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	(void)argv;
// 	t_env	env;
// 	env.gb_list = NULL;

// 	// set_vec3(&env.eye.pos, 3, 2, -1);
// 	env.obj_list = get_obj_list(&env.gb_list);
// 	env.light_list = get_light_list(&env.gb_list);

// 	set_vec3(&env.eye.pos, 0, 0, -5);
// 	set_vec3(&env.eye.orientation, 0,0,1);

// 	env.eye.distance_to_window = get_distance_to_window(100);
// 	printf("distance_to_window is %f\n", env.eye.distance_to_window);
// 	env.mlx = mlx_init();
// 	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
// 	set_event(&env);
// 	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
// 	// color_img(&env);
// 	test_rect(&env);
// 	// ft_dlstclear(&gb_list, free);
// 	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
// 	printf("PUT IMAGE TO WINDOW\n");
// 	mlx_loop(env.mlx);
// }

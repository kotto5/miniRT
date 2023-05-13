/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/13 19:25:30 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

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
// 	make_img6(&env);
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
// 	// make_img6(&env);
// 	test_rect(&env);
// 	// ft_dlstclear(&gb_list, free);
// 	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
// 	printf("PUT IMAGE TO WINDOW\n");
// 	mlx_loop(env.mlx);
// }

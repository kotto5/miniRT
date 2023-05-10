/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/08 12:59:29 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_env	env;

	env.gb_list = NULL;
	set_vec3(&env.eye.pos, 0, 0, -5);
	set_vec3(&env.eye.orientation, 0,0,1);
	env.eye.distance_to_window = get_distance_to_window(90);
	printf("distance_to_window is %f\n", env.eye.distance_to_window);

	env.obj_list = get_obj_list(&env.gb_list);
	env.light_list = get_light_list(&env.gb_list);
	env.obj_tree = get_obj_tree(&env);

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	set_event(&env);
	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
	make_img6(&env);
	// ft_dlstclear(&gb_list, free);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	printf("PUT IMAGE TO WINDOW\n");
	mlx_loop(env.mlx);
}

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


// int	main()
// {
// 	t_intersection	intersection;
// 	t_ray	ray;
	// t_obj	*obj;
	// t_rect	*rect;
// 	t_dlist	*gb_list;

// gb_list = NULL;
// rect = make_rect_instance(get_vec(2,2,2), get_vec(6, 8, 6), &gb_list);
// obj = new_obj(O_RECT, get_t_refrect(b_color_get(0,0,0,0), b_color_get(0, 1,1,0), b_color_get(0,0,1,0), 5, false, (t_bright_color){1.0, 1.0, 1.0, 1.0}),
// rect, &gb_list);

// 	// intersection = get_intersection_rect(ray, obj);

// 	// if (intersection.does_intersect)
// 	// {
// 	// 	printf("1======OK======!\n");
// 	// 	// print_vec(intersection.position, "pos");
// 	// 	// print_vec(intersection.vertical_dir, "dir");
// 	// }
// 	// else
// 	// 	printf("1=====NO======!\n");

// 	ray.pos = (t_vec3){0,0,10};ray.dir = (t_vec3){0,0,1};rect->bound1 = get_vec(2,2,2);rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");


// // 入ってて前向き
// 	ray.pos = (t_vec3){0,0,0}; ray.dir = (t_vec3){0,0,1}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// // 入ってて後ろ向き
// // ray.pos = (t_vec3){5,5,5}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// ray.pos = (t_vec3){0,0,0}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// // 視点をちょっと前
// ray.pos = (t_vec3){1,1,1}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("視点をちょっと前======OK======!\n");
// 	else
// 		printf("視点をちょっと前=====NO======!\n");

// // ぎり入ってる
// ray.pos = (t_vec3){3,3,3}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(0,0,0); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("ぎり入ってる======OK======!\n");
// 	else
// 		printf("ぎり入ってる=====NO======!\n");

// // ぎり入ってる
// ray.pos = (t_vec3){3,3,3}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(0.9,0.9,0.9); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("ぎりてすと======OK======!\n");
// 	else
// 		printf("ぎりてすと=====NO======!\n");

// // なぞ
// ray.pos = (t_vec3){5,5,5}; ray.dir = (t_vec3){0,0,-1}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("なぞ======OK======!\n");
// 	else
// 		printf("なぞ=====NO======!\n");


// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){0,1,0}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(2,2,2); rect->bound2 = get_vec(6, 8, 6);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");






// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-1,1,1);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("333333======OK======!\n");
// 	else
// 		printf("333333=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-1,-1,1);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-3,-3,-3);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-3,1,1);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");

// ray.pos = (t_vec3){0,0,10}; ray.dir = (t_vec3){1,0,0}; rect->bound1 = get_vec(-2,-2,-2); rect->bound2 = get_vec(-3,-3,-3);
// 	intersection = get_intersection_rect(ray, obj);
// 	if (intersection.does_intersect)
// 		printf("2======OK======!\n");
// 	else
// 		printf("2=====NO======!\n");
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q miniRT");
// }
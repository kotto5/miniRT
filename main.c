/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/02 23:32:15 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"


int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_env	env;
	env.gb_list = NULL;

	// set_vec3(&env.eye.pos, 3, 2, -1);
	set_vec3(&env.eye.pos, 3, 0, -5);
	set_vec3(&env.eye.orientation, 0,5,0);
	env.eye.distance_to_window = get_distance_to_window(160);
	printf("distance_to_window is %f\n", env.eye.distance_to_window);
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

__attribute__((destructor)) static void destructor()
{
	system("leaks -q miniRT");
}

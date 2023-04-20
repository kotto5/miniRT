/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/20 16:13:38 by kakiba           ###   ########.fr       */
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
	printf("key is :%d\n", key);
	// make_img2(&env->img, env->eye);
	// mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	t_env	env;
	t_dlist	*gb_list;
	gb_list = NULL;
	set_vec3(&env.eye.pos, 0, 0, -5);

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	// set_event();
	mlx_key_hook(env.win, key_event, &env);
	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
	make_img3(&env.img, env.eye, &gb_list);
	printf("img made\n");
	// make_img2(&env.img, env.eye);
	// make_img(&env.img);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	printf("put window\n");
	mlx_loop(env.mlx);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q miniRT");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:49:04 by shtanemu          #+#    #+#             */
/*   Updated: 2023/04/28 02:48:47 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "minirt.h"
#include "keycode.h"
#include "vector.h"

static void	init_window(void **mlx, void **win, t_data *img)
{
	*mlx = mlx_init();
	*win = mlx_new_window(*mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	img->img = mlx_new_image(*mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
									&(img->line_length), \
									&(img->endian));
}

static int	exit_proc(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	exit_with_esc(int keycode, t_env *env)
{
	if (keycode == ESC)
		exit_proc(env);
	return (0);
}

// put_ball(&env);
void	manage_window(void)
{
	t_env	env;

	init_window(&env.mlx, &env.win, &env.img);
	put_plane(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_key_hook(env.win, exit_with_esc, &env);
	mlx_hook(env.win, 17, 0L, exit_proc, &env);
	mlx_loop(env.mlx);
}

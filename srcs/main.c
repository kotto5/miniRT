/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/04 15:33:25 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "conf_validation.h"

int	initialize_env(t_env *env)
{
	env->mlx = mlx_init();
	if (env->mlx == NULL)
		return (ERROR);
	env->win = mlx_new_window(env->mlx, \
								WIN_WIDTH, \
								WIN_HEIGHT, \
								"Hello world!");
	if (env->win == NULL)
		return (ERROR);
	env->img.img = mlx_new_image(env->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (env->img.img == NULL)
		return (ERROR);
	env->img.addr = mlx_get_data_addr(env->img.img, \
										&env->img.bits_per_pixel, \
										&env->img.line_length, \
										&env->img.endian);
	set_event(env);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (is_valid(argv[1], argc) == false)
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
	return (0);
}

// #include <libc.h>

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q miniRT");
// }

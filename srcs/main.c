/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:22:52 by shtanemu          #+#    #+#             */
/*   Updated: 2023/04/25 01:17:27 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdbool.h>
#include "minirt.h"
#include "vector.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + \
			(y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_window(void **mlx, void **win, t_data *img)
{
	*mlx = mlx_init();
	*win = mlx_new_window(*mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	img->img = mlx_new_image(*mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
									&(img->line_length), \
									&(img->endian));
}

static void	window_management(void)
{
	t_env	env;

	init_window(&env.mlx, &env.win, &env.img);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_loop(env.mlx);
}

int	main_minirt(void)
{
	window_management();
	return (0);
}

int	main(void)
{
	main_minirt();
	return (0);
}

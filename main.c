/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 12:32:17 by kakiba           ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char	*ptr;
	char	*ptr2;
	char	*ptr3;
	t_dlist	*gc;
	ptr = ft_galloc(10, &gc);
	ptr2 = ft_galloc(10, &gc);
	ptr3 = ft_galloc(10, &gc);
	ft_dlstdelete(&gc, ptr, free);
	ft_dlstdelete(&gc, ptr2, free);
	ft_dlstdelete(&gc, ptr3, free);

	// ft_exit(0, &gc);
	return (0);
	// t_mlx	mlx;

	// mlx.mlx = mlx_init();
	// mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	// mlx.img.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	// make_img(&mlx.img);
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	// mlx_loop(mlx.mlx);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q miniRT");
}

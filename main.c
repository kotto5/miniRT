/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:07:28 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/15 11:17:06 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	do_nothing(void *ptr){
	(void)ptr;
	return ;
}

int	main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char	*ptr;
	t_list	*alloc_list;

	alloc_list = NULL;
	if (alloc_list)
	{
		printf("JJJJ\n");
	}
	else
		printf("HHHH\n");

	ptr = ft_galloc(10, &alloc_list);
	ptr = ft_galloc(13, &alloc_list);
	ptr = ft_galloc(13, &alloc_list);
	ptr[0] = 'A';
	ptr[1] = '\0';
	if (ptr == NULL)
		printf("HEY!!!\n");
	else
		printf("ptr pointer %p\n", ptr);
	// free (ptr);
	if (alloc_list)
		printf("%p \n", alloc_list->content);
	else
		printf("YEAHHHH!!!!!!\n");
	ft_lstclear(&alloc_list, free);
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

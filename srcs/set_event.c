/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:54:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/31 16:36:02 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	key_event(int key, void *data);
int	mouse_event(int button, int x, int y, void *data);

static int	exit_proc(int status, void *gc)
{
	ft_dlstclear(gc, free);
	exit(status);
	return (0);
}

int	mouse_event(int button, int x, int y, void *data)
{
	t_env	*env;

	(void)x;
	(void)y;
	env = (t_env *)data;
	if (button == 1)
		env->camera->origin.z += 0.1;
	if (button == 2)
		env->camera->origin.z -= 0.1;
	if (button == 1 || button == 2)
	{
		printf("button is %d\n", button);
		env->camera->origin.z -= 0.1;
		env->camera = make_camera(env->camera->fov, \
			env->camera->origin, \
			env->camera->orientation);
	}
	else
	{
		printf("button is %d\n", button);
		return (0);
	}
	color_img(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}

// the function that deals with mouse movement
// if mouse move to right, then move the camera to right
int	mouse_move(int x, int y, void *data)
{
	(void)x;
	(void)y;
	(void)data;
	printf("mouse move x is %d\n", x);
	printf("mouse move y is %d\n", y);
	return (0);
}

int	key_event(int key, void *data)
{
	t_env	*env;

	env = (t_env *)data;
	if (key == ALLOW_DOWN)
		env->eye->pos.y += 0.1;
	else if (key == ALLOW_UP)
		env->eye->pos.y -= 0.1;
	else if (key == ALLOW_LEFT)
		env->eye->pos.x += 0.1;
	else if (key == ALLOW_RIGHT)
		env->eye->pos.x -= 0.1;
	else if (key == KEY_Z)
		env->eye->pos.z += 0.1;
	else if (key == KEY_X)
		env->eye->pos.z -= 0.1;
	else if (key == KEY_ESC)
		exit_proc(0, &env->gb_list);
	else
	{
		printf("key is :%d\n", key);
		return (0);
	}
	color_img(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}

void	set_event(t_env *env)
{
	mlx_key_hook(env->win, key_event, env);
	mlx_mouse_hook(env->win, mouse_event, env);
	mlx_hook(env->win, 17, 0L, exit_proc, &env);
	mlx_hook(env->win, 6, 1L << 6, mouse_move, env);
}

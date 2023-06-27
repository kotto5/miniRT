/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 22:54:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/27 14:57:04 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int	key_event(int key, void *data);

int	exit_proc(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	gc_clear();
	if (env->mlx == NULL)
		exit(EXIT_SUCCESS);
	if (env->win)
	{
		free (env->mlx);
		exit(EXIT_SUCCESS);
	}
	if (env->img.img == NULL)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(EXIT_SUCCESS);
	}
	mlx_destroy_image(env->mlx, env->img.img);
	mlx_destroy_window(env->mlx, env->win);
	free(env->mlx);
	return (0);
}

static t_camera	*remake_camera(t_camera *camera)
{
	t_camera	*new_camera;

	new_camera = make_camera(camera->fov,
			camera->origin,
			camera->orientation);
	if (new_camera == NULL)
		return (camera);
	new_camera->fov = camera->fov;
	new_camera->origin = camera->origin;
	new_camera->orientation = camera->orientation;
	free (camera);
	return (new_camera);
}

static int	set_env_eye(t_env *env, int key)
{
	if (key == ALLOW_DOWN)
		env->camera->origin.y += 0.1;
	else if (key == ALLOW_UP)
		env->camera->origin.y -= 0.1;
	else if (key == ALLOW_LEFT)
		env->camera->origin.x += 0.1;
	else if (key == ALLOW_RIGHT)
		env->camera->origin.x -= 0.1;
	else if (key == KEY_Z)
		env->camera->origin.z += 0.1;
	else if (key == KEY_X)
		env->camera->origin.z -= 0.1;
	else if (key == KEY_ESC)
		exit_proc(env);
	else
		return (1);
	env->camera = remake_camera(env->camera);
	return (0);
}

int	key_event(int key, void *data)
{
	t_env	*env;

	env = (t_env *)data;
	if (set_env_eye(env, key) == 1)
		return (0);
	color_img(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	mlx_loop(env->mlx);
	return (0);
}

void	set_event(t_env *env)
{
	mlx_key_hook(env->win, key_event, env);
	mlx_hook(env->win, 17, 0L, exit_proc, env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:23:01 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/21 15:48:34 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "all.h"

int	get_nearest_intersection(t_intersection_info *info, \
								t_scene *scene, \
								t_ray *ray)
{
	t_dlist			*node;
	t_obj			*obj_content;
	t_intersection	tmp;

	node = scene->obj_list;
	info->intersection.does_intersect = false;
	while (node)
	{
		obj_content = node->content;
		tmp = obj_content->get_intersection(*ray, obj_content);
		if (tmp.does_intersect && (info->intersection.does_intersect \
									== false \
									|| tmp.distance \
										< info->intersection.distance))
		{
			info->intersection = tmp;
			info->obj = obj_content;
		}
		node = node->next;
	}
	return (SUCCESS);
}

t_bright_color	*ray_trace(t_bright_color *b_color, \
							t_scene *scene, \
							t_ray *ray)
{
	t_intersection_info	info;
	t_dlist				*node;

	ft_memset(b_color, 0, sizeof(t_bright_color));
	get_nearest_intersection(&info, scene, ray);
	if (info.intersection.does_intersect)
	{
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, \
									get_color_with_at(scene, \
														&info, \
														node->content, \
														ray));
			node = node->next;
		}
	}
	return (b_color);
}

static void	print_time(int a)
{
	static long		before;
	static long		now;
	struct timeval	t1;
	long			s_time;

	if (gettimeofday(&t1, NULL))
		return ;
	s_time = (long)(t1.tv_sec);
	now = s_time * 10000000 + (long)(t1.tv_usec);
	if (before == 0)
		printf("[%d]time %d\n", a, 0);
	else
		printf("[%d]time %ld\n", a, now - before);
	before = now;
}

static int	init_scene(t_scene *scene, t_env *env)
{
	scene->obj_list = env->obj_list;
	scene->light_list = env->light_list;
	scene->am_light = env->am_light;
	return (0);
}

int	color_img(t_env *env)
{
	t_bright_color	ref_color;
	t_scene			scene;
	int				x;
	int				y;

	init_scene(&scene, env);
	print_time(3);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_ray(env->camera, x, y, &env->eye);
			ray_trace(&ref_color, &scene, &env->eye);
			mlx_put_to_img(&env->img, x, y, \
							to_img_color_from_b_color(&ref_color));
			x++;
		}
		y++;
	}
	print_time(4);
	return (SUCCESS);
}

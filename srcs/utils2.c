/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 23:03:52 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/01 14:55:19 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <sys/time.h>

void	add_sum_to_b_color(t_bright_color *b_color,
	t_bright_color sum, t_rt rt_info)
{
	if (rt_info.depth == 0)
		*b_color = sum;
	else
		*b_color = b_color_add(*b_color,
				b_color_mult(sum, rt_info.perfect_reflectance));
}

void	clc_light_effect(t_intersection_info *info,
	t_scene *scene, t_ray *ray, t_bright_color *sum)
{
	t_dlist			*node;

	*sum = b_color_mult(info->obj->ref.am, *scene->am_light);
	node = scene->light_list;
	while (node)
	{
		*sum = b_color_add(*sum,
				get_color_with_at(scene, info, node->content, ray));
		node = node->next;
	}
}

void	print_time(int a)
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

int	init_scene(t_scene *scene, t_env *env)
{
	scene->obj_list = env->obj_list;
	scene->light_list = env->light_list;
	scene->am_light = env->am_light;
	return (0);
}

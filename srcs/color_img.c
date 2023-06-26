/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:23:01 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/26 21:19:05 by kakiba           ###   ########.fr       */
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

t_ray	*make_reray(t_ray *ray, t_intersection_info info)
{
	t_ray			*re_ray;
	t_vec3			v;
	t_vec3			v2;
	double			dot_product;

	re_ray = (t_ray *)malloc(sizeof(t_ray));
	if (!re_ray)
		return (NULL);
	v = vec_mult(ray->dir, -1);
	v2 = vec_normalize(info.intersection.vertical_dir);
	dot_product = vec_dot(v2, v);
	if (dot_product < 0.0)
		return (NULL);
	re_ray->dir = vec_sub(vec_mult(v2, 2.0 * dot_product), v);
	re_ray->pos = vec_add(info.intersection.position, vec_mult(re_ray->dir, EPSILON));
	return (re_ray);
}

t_bright_color	*ray_trace_pr(t_bright_color *b_color, \
							t_scene *scene, \
							t_ray *ray, \
							t_rt rt_info)
{
	t_intersection_info	info;
	t_dlist				*node;
	t_ray				*reray;
	t_bright_color		sum;

	if (rt_info.depth > 5)
		return (b_color);
	// ft_bzero(&sum, sizeof(t_bright_color));
	get_nearest_intersection(&info, scene, ray);
	if (info.intersection.does_intersect)
	{
		node = scene->light_list;
		while (node)
		{
			sum = b_color_add(sum, get_color_with_at(scene, &info, node->content, ray));
			// *b_color = b_color_add(*b_color, get_color_with_at(scene,
			// 	&info, node->content, ray));
			node = node->next;
		}
		if (info.obj->ref.use_perfect_reflectance)
		{
			rt_info.perfect_reflectance = b_color_mult(rt_info.perfect_reflectance, info.obj->ref.perfect_reflectance);
			rt_info.depth++;
			// free (rt_info.ray);
			// rt_info.ray = make_reray(ray, info);
			reray = make_reray(ray, info);
			if (reray)
			{
				ray_trace_pr(&sum, scene, reray, rt_info);
				// ray_trace_pr(b_color, scene, reray, depth + 1);
				// ret = ray_trace_pr(&ret, scene, reray, depth + 1);
				// *b_color = b_color_add(*b_color, b_color_mult(*ret, \
				// 	info.obj->ref.perfect_reflectance));
				free(reray);
			}
		}
	}
	if (rt_info.depth == 1)
		*b_color = sum;
	else
		*b_color = b_color_add(*b_color, b_color_mult(sum, rt_info.perfect_reflectance));
	// *b_color = b_color_add(*b_color, b_color_mult(sum, rt_info.perfect_reflectance));
	return (b_color);
}

t_bright_color	*ray_trace(t_bright_color *b_color, \
							t_scene *scene, \
							t_ray *ray)
{
	t_intersection_info	info;
	t_dlist				*node;
	// t_bright_color		sum;
	t_ray				*reray;

	ft_memset(b_color, 0, sizeof(t_bright_color));
	// ft_memset(&sum, 0, sizeof(t_bright_color));
	get_nearest_intersection(&info, scene, ray);
	if (info.intersection.does_intersect)
	{
		node = scene->light_list;
		while (node)
		{
			// sum = b_color_add(sum, get_color_with_at(scene, &info, node->content, ray));

			*b_color = b_color_add(*b_color, get_color_with_at(scene, \
				&info, node->content, ray));
			node = node->next;
		}
		if (info.obj->ref.use_perfect_reflectance)
		{
			reray = make_reray(ray, info);
			if (reray)
			{
				ray_trace_pr(b_color, scene, reray, (t_rt){info.obj->ref.perfect_reflectance, 1});
				free (reray);
			}
			// *b_color = b_color_add(*b_color, b_color_mult(*ret, \
			// 	info.obj->ref.perfect_reflectance));
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

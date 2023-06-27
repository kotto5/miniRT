/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:23:01 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/27 13:00:08 by kakiba           ###   ########.fr       */
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
	re_ray->pos = vec_add(info.intersection.position, \
		vec_mult(re_ray->dir, EPSILON));
	return (re_ray);
}

	// if (rt_info.depth == 0)
	// 	sum = b_color_mult(info.obj->ref.am, *scene->am_light);

	// *sum = b_color_mult(info->obj->ref.am, *scene->am_light);

	// 	*b_color = b_color_add(*b_color,
	// 			b_color_mult(sum, rt_info.perfect_reflectance));

void	ray_trace(t_bright_color *b_color, \
							t_scene *scene, \
							t_ray *ray, \
							t_rt rt_info)
{
	t_intersection_info	info;
	t_ray				*reray;
	t_bright_color		sum;

	if (rt_info.depth > 5)
		return ;
	ft_bzero(&sum, sizeof(t_bright_color));
	get_nearest_intersection(&info, scene, ray);
	if (info.intersection.does_intersect == false)
		return ;
	clc_light_effect(&info, scene, ray, &sum);
	if (info.obj->ref.use_perfect_reflectance)
	{
		reray = make_reray(ray, info);
		if (reray == NULL)
			return ;
		ray_trace(&sum, scene, reray, \
			(t_rt){info.obj->ref.perfect_reflectance, rt_info.depth + 1});
		free(reray);
	}
	add_sum_to_b_color(b_color, sum, rt_info);
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
			ft_bzero(&ref_color, sizeof(t_bright_color));
			set_ray(env->camera, x, y, &env->eye);
			ray_trace(&ref_color, &scene,
				&env->eye, (t_rt){(t_bright_color){0, 0, 0, 0}, 0});
			mlx_put_to_img(&env->img, x, y, \
							to_img_color_from_b_color(&ref_color));
			x++;
		}
		y++;
	}
	print_time(4);
	return (SUCCESS);
}

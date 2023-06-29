/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_with_at.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:04:07 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 15:21:05 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_intersection(t_intersection intersection)
{
	printf("distance %f, inside %d\n", intersection.distance, \
										intersection.is_inside);
	print_vec(intersection.position, "inter position");
	print_vec(intersection.vertical_dir, "inter vertical");
}

bool	do_through_other_obj_by_light(t_dlist *obj_list, \
										t_lightsource *light, \
										t_intersection_info *info)
{
	t_dlist				*node;
	t_obj				*instance;
	t_ray				light_ray;
	t_intersection		intersection;
	const t_lighting	lighting = \
							light->lighting_at(info->intersection.position, \
												light);

	light_ray.dir = lighting.incident_to_light;
	light_ray.pos = vec_add(info->intersection.position, \
							vec_mult(info->intersection.vertical_dir , EPS));
							// vec_mult(lighting.incident_to_light , EPS));
	node = obj_list;
	while (node)
	{
		instance = node->content;
		intersection = instance->get_intersection(light_ray, instance);
		if (intersection.does_intersect \
			&& intersection.distance < lighting.distance)
			return (true);
		node = node->next;
	}
	return (false);
}

t_bright_color	get_color_with_at(t_scene *scene, \
									t_intersection_info *info, \
									t_lightsource *light, t_ray *ray)
{
	t_bright_color	ref;
	t_point_light	*p_light;

	p_light = light->instance;
	ft_memset(&ref, 0, sizeof(t_bright_color));
	if (info->intersection.does_intersect == true)
	{
		if (do_through_other_obj_by_light(scene->obj_list, \
											light, info))
			return (ref);
		// else if (info->obj->is_closed \
		// 			&& info->intersection.is_inside \
		// 			!= info->obj->is_inside_point(info->obj, p_light->pos))
		// 	return (ref);
		else
			ref = get_ref6(info, light, *ray, scene);
	}
	return (ref);
}

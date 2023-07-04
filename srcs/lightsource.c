/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:13:02 by shtanemu          #+#    #+#             */
/*   Updated: 2023/07/03 14:28:33 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "all.h"

t_spot_light	*make_spot_light_info(t_vec3 position, \
										t_vec3 orientation, \
										double apex_angle, \
										t_bright_color intensity)
{
	t_spot_light	*spot_light;

	spot_light = gc_malloc(sizeof(t_spot_light));
	if (spot_light == NULL)
		return (NULL);
	spot_light->intensity = intensity;
	spot_light->pos = position;
	spot_light->orientation = orientation;
	spot_light->apex_angle = apex_angle / 2.0 * PI / 180.0;
	return (spot_light);
}

t_point_light	*make_point_light_info(t_vec3 position, \
										t_bright_color intensity)
{
	t_point_light	*light;

	light = gc_malloc(sizeof(t_point_light));
	if (light == NULL)
		return (NULL);
	light->intensity = intensity;
	light->pos = position;
	return (light);
}

t_lighting	lighting_at_point(t_vec3 position, t_lightsource *light)
{
	t_lighting		lighting;
	t_point_light	*info;
	t_vec3			vec;

	info = light->instance;
	vec = vec_sub(info->pos, position);
	lighting.incident_to_light = vec_normalize(vec);
	lighting.distance = vec_mag(vec);
	lighting.intensity.t = info->intensity.t;
	lighting.intensity.r = info->intensity.r;
	lighting.intensity.g = info->intensity.g;
	lighting.intensity.b = info->intensity.b;
	return (lighting);
}

t_parallel_light	*make_parallel_light_info(t_vec3 dir, \
												double intensity, \
												t_dlist **gb_list)
{
	t_parallel_light	*light;

	(void)intensity;
	light = ft_galloc(sizeof(t_parallel_light), gb_list);
	light->dir = dir;
	return (light);
}

t_lightsource	*new_light(t_lighttype type, void *light_info)
{
	t_lightsource	*light;

	if (light_info == NULL)
		return (NULL);
	light = gc_malloc(sizeof(t_lightsource));
	if (light == NULL)
		return (NULL);
	light->type = type;
	light->instance = light_info;
	if (type == L_POINT)
		light->lighting_at = lighting_at_point;
	else if (type == L_SPOT)
		light->lighting_at = spot_lighting_at_point;
	else
		light->lighting_at = NULL;
	return (light);
}

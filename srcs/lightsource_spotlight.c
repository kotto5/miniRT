/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource_spotlight.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:25:27 by shtanemu          #+#    #+#             */
/*   Updated: 2023/07/03 14:25:27 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "all.h"

static bool	is_inside_spotlight(\
	t_vec3 *intersection, t_vec3 *spotlight, t_vec3 *ov, double apex_angle\
)
{
	const double	height = vec_mag(vec_sub(*spotlight, *intersection));
	const t_vec3	add = vec_mult(*ov, height);
	const t_vec3	center = vec_add(*spotlight, add);
	const double	r = fabs(height * tan(apex_angle));
	const double	dis = vec_mag(vec_sub(center, *intersection));

	if (dis >= r)
		return (false);
	return (true);
}

t_lighting	spot_lighting_at_point(t_vec3 position, t_lightsource *light)
{
	t_lighting		lighting;
	t_spot_light	*info;
	t_vec3			vec;

	info = light->instance;
	vec = vec_sub(info->pos, position);
	lighting.incident_to_light = vec_normalize(vec);
	lighting.distance = vec_mag(vec);
	if (is_inside_spotlight(\
			&position, \
			&(info->pos), \
			&(info->orientation), \
			info->apex_angle) == false)
	{
		lighting.intensity.t = 0.00;
		lighting.intensity.r = 0.00;
		lighting.intensity.g = 0.00;
		lighting.intensity.b = 0.00;
		return (lighting);
	}
	lighting.intensity.t = info->intensity.t;
	lighting.intensity.r = info->intensity.r;
	lighting.intensity.g = info->intensity.g;
	lighting.intensity.b = info->intensity.b;
	return (lighting);
}

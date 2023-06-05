/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_instance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:43:47 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/05 16:44:21 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_sphere	*make_sphere_instance(t_vec3 origin, double r)
{
	t_sphere	*instance;

	instance = gc_malloc(sizeof(t_sphere));
	if (instance == NULL)
		return (NULL);
	instance->r = r;
	instance->pos = origin;
	return (instance);
}

t_plane	*make_plane_instance(t_vec3 vertical, t_vec3 point)
{
	t_plane	*instance;

	instance = gc_malloc(sizeof(t_plane));
	if (instance == NULL)
		return (NULL);
	instance->vertical = vec_normalize(vertical);
	instance->position = point;
	return (instance);
}

t_cylinder	*make_cylinder_instance(t_vec3 vertical, t_vec3 point, double r, double height)
{
	t_cylinder	*instance;

	instance = gc_malloc(sizeof(t_cylinder));
	if (instance == NULL)
		return (NULL);
	instance->r = r;
	instance->vertical = vec_normalize(vertical);
	instance->position = point;
	instance->height = height;
	return (instance);
}

t_rect	*make_rect_instance(t_vec3 bound1, t_vec3 bound2)
{
	t_rect	*instance;

	instance = gc_malloc(sizeof(t_rect));
	if (instance == NULL)
		return (NULL);
	instance->bound1.x = get_min_double(bound1.x, bound2.x);
	instance->bound2.x = get_max_double(bound1.x, bound2.x);
	instance->bound1.y = get_min_double(bound1.y, bound2.y);
	instance->bound2.y = get_max_double(bound1.y, bound2.y);
	instance->bound1.z = get_min_double(bound1.z, bound2.z);
	instance->bound2.z = get_max_double(bound1.z, bound2.z);

	return (instance);
}

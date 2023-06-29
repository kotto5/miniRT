/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:42:52 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 13:38:36 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	set_params(t_obj *obj, t_objtype type)
{
	if (type == O_SPHERE)
	{
		obj->get_intersection = get_intersection_sphere;
		obj->is_inside_point = is_inside_sphere;
		obj->is_closed = true;
	}
	else if (type == O_PLANE)
	{
		obj->get_intersection = get_intersection_plane;
		obj->is_closed = false;
	}
	else if (type == O_CYLINDER)
	{
		obj->get_intersection = get_intersection_cylinder;
		// obj->is_inside_point = is_inside_cylinder;
		obj->is_closed = false;
	}
	else if (type == O_RECT)
		obj->get_intersection = get_intersection_rect;
	else if (type == O_CONE)
	{
		obj->get_intersection = get_intersection_cone;
		obj->is_closed = false;
	}
	else
		obj->get_intersection = NULL;
	return (0);
}

t_obj	*new_obj(t_objtype type, t_reflect ref, void *obj_info)
{
	t_obj	*obj;

	if (obj_info == NULL)
		return (NULL);
	obj = gc_malloc(sizeof(t_obj));
	if (obj == NULL)
		return (NULL);
	ft_memset(obj, 0, sizeof(t_obj));
	obj->ref = ref;
	obj->type = type;
	obj->instance = obj_info;
	obj->ref.use_perfect_reflectance = false;
	set_params(obj, type);
	return (obj);
}

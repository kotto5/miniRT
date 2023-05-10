#include "all.h"

t_circle	*make_circle_instance(t_vec3 origin, double r, t_dlist **gb_list)
{
	t_circle	*instance;

	instance = ft_galloc(sizeof(t_circle), gb_list);
	if (instance == NULL)
		return (NULL);
	instance->r = r;
	instance->pos = origin;
	return (instance);
}

t_plane	*make_plane_instance(t_vec3 vertical, t_vec3 point, t_dlist **gb_list)
{
	t_plane	*instance;

	instance = ft_galloc(sizeof(t_plane), gb_list);
	if (instance == NULL)
		return (NULL);
	instance->vertical = vertical;
	instance->position = point;
	return (instance);
}

t_cylinder	*make_cylinder_instance(t_vec3 vertical, t_vec3 point, double r, t_dlist **gb_list)
{
	t_cylinder	*instance;

	instance = ft_galloc(sizeof(t_cylinder), gb_list);
	if (instance == NULL)
		return (NULL);
	instance->r = r;
	instance->vertical = vertical;
	instance->position = point;
	return (instance);
}

t_rect	*make_rect_instance(t_vec3 bound1, t_vec3 bound2, t_dlist **gb_list)
{
	t_rect	*instance;

	instance = ft_galloc(sizeof(t_rect), gb_list);
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

t_obj	*new_obj(t_objtype type, t_reflect ref, void *obj_info, t_dlist **alloc_list)
{
	t_obj	*obj;

	if (obj_info == NULL)
		return (NULL);
	obj = ft_galloc(sizeof(t_obj), alloc_list);
	// obj = malloc(sizeof(t_obj));
	if (obj == NULL)
		return (NULL);
	obj->ref = ref;
	obj->type = type;
	obj->instance = obj_info;
	if (type == O_CIRCLE)
		obj->get_intersection = get_intersection_circle;
	else if (type == O_PLANE)
		obj->get_intersection = get_intersection_plane;
	else if (type == O_CYLINDER)
		obj->get_intersection = get_intersection_cylinder;
	else if (type == O_RECT)
		obj->get_intersection = get_intersection_rect;
	else
		obj->get_intersection = NULL;
	return (obj);
}

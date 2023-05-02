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

t_obj	*new_obj(t_objtype type, t_reflect ref, void *obj_info, t_dlist **alloc_list)
{
	t_obj	*obj;

	if (obj_info == NULL)
		return (NULL);
	obj = ft_galloc(sizeof(t_obj), alloc_list);
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
	else
		obj->get_intersection = NULL;
	return (obj);
}

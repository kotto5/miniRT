#include "includes/all.h"

// t_obj	*new_circle(t_obj *obj, t_circle *circle)
// {
// 	obj->type = O_CIRCLE;
// 	obj->instance = circle;
// 	obj->get_intersection = get_intersection_circle;
// 	return (obj);
// }

t_circle	*make_circle_instance(t_vec3 origin, double r, t_dlist **gb_list)
{
	t_circle	*instance;

	instance = ft_galloc(sizeof(t_circle), gb_list);
	if (instance == NULL)
		return (NULL);
	instance->r = r;
	instance->pos = origin;
	// instance->ref = ref;
	// instance->ref.d_am = 0.1;
	// instance->ref.d_di = 0.69;
	// instance->ref.d_sp = 0.3;
	// instance->ref.sp_shininess = 0.0;
	return (instance);
}

// t_plane	*make_plane_instance(t_vec3 vertical, t_reflect ref, t_dlist **gb_list)
t_plane	*make_plane_instance(t_vec3 vertical, t_dlist **gb_list)
{
	t_plane	*instance;

	instance = ft_galloc(sizeof(t_plane), gb_list);
	if (instance == NULL)
		return (NULL);
	instance->vertical = vertical;
	// instance->vertical.x = 0;
	// instance->vertical.y = 1;
	// instance->vertical.z = 0;
	// instance->ref = ref;
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
	else
		obj->get_intersection = NULL;
	return (obj);
}

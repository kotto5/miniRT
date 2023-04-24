#include "includes/all.h"

t_obj	*new_circle(t_obj *obj, t_circle *circle)
{
	obj->type = O_CIRCLE;
	obj->instance = circle;
	obj->get_intersection = get_circle_intersection;
	return (obj);
}

t_circle	*make_circle_instance(t_vec3 origin, double r, t_reflect ref, t_dlist **gb_list)
{
	t_circle	*instance;

	instance = ft_galloc(sizeof(t_circle), gb_list);
	if (instance == NULL)
		return (NULL);
	instance->r = r;
	instance->pos = origin;
	instance->ref = ref;
	// instance->ref.d_am = 0.1;
	// instance->ref.d_di = 0.69;
	// instance->ref.d_sp = 0.3;
	// instance->ref.d_sp_shininess = 0.0;
	return (instance);
}

t_obj	*new_obj(t_objtype type, void *obj_info, t_dlist **alloc_list)
{
	t_obj	*obj;

	if (obj_info == NULL)
		return (NULL);
	obj = ft_galloc(sizeof(obj), alloc_list);
	if (obj == NULL)
		return (NULL);
	obj->type = type;
	obj->instance = obj_info;
	if (type == O_CIRCLE)
		obj->get_intersection = get_circle_intersection;
	else
		obj->get_intersection = NULL;
	return (obj);
}

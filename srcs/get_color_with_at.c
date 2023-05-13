#include "all.h"

bool	do_through_other_obj_by_light(t_dlist *obj_list, t_lightsource *light, t_intersection_info *info)
{
	t_dlist	*node;
	t_obj	*instance;
	t_ray	light_ray;
	t_intersection	intersection;
	t_lighting		lighting = light->lighting_at(info->intersection.position, light);
	double			epsilon = 1.0 / 32;

	light_ray.dir = lighting.incident_to_light;
	light_ray.pos = info->intersection.position;
	lighting.distance += epsilon; // これで弾くのって instance == info->obj のケースじゃないの？
	node = obj_list;
	while (node)
	{
		instance = node->content;
		if (instance == info->obj)
		{
			node = node->next;
			continue ;
		}
		intersection = instance->get_intersection(light_ray, instance);
		if (intersection.does_intersect && intersection.distance < lighting.distance)
		{
			return (true);
		}
		node = node->next;
	}
	return (false);
}

t_bright_color	get_color_with_at(t_scene *scene, t_intersection_info *info, t_lightsource *light, t_ray *ray)
{
	t_bright_color	ref;
	ft_memset(&ref, 0, sizeof(t_bright_color));

	if (info->intersection.does_intersect == true)
	{
		if (do_through_other_obj_by_light(scene->obj_list, light, info))
			return (ref);
		else
			ref = get_ref6(info, light, *ray, scene);
			// ref = get_ref6(info->intersection, info->obj->ref, light, *ray);
	}
	return (ref);
}

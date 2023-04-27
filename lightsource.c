#include "all.h"

// t_point_light	*make_point_light_info(t_vec3 position, t_color intensity, t_dlist **gb_list)
t_point_light	*make_point_light_info(t_vec3 position, double intensity, t_dlist **gb_list)
{

	t_point_light	*light;
	light = ft_galloc(sizeof(t_point_light), gb_list);
	// light->intensity = intensity;
	light->d_intensity = intensity;
	light->pos = position;
	return (light);
}

t_lighting	lighting_at_point(t_vec3 position, t_lightsource *light)
{
	t_lighting	lighting;
	t_point_light	*info;
	t_vec3		vec;

	info = light->instance;
	// vec = vec_sub(position, info->pos);
	vec = vec_sub(info->pos, position);
	// printf("LIGHT 7\n");

	lighting.incident_to_light = vec_normilize(vec);
	// printf("LIGHT 8\n");
	lighting.distance = vec_mag(vec);
	// printf("LIGHT 9\n");

	// lighting.intensity = color_mult(info->d_intensity, 1.0 / (1.0 + lighting.distance));
	// lighting.d_intensity = info->d_intensity * (1.0 / (1.0 + lighting.distance));
	lighting.d_intensity = 20 - lighting.distance;
	if (lighting.d_intensity > 1)
		lighting.d_intensity = 1;
	if (lighting.d_intensity < 0)
		lighting.d_intensity = 0;
	// 距離の二乗に反比例 暗すぎるかも
	// printf("LIGHT 4\n");
	// lighting.d_intensity = info->d_intensity * 1.0 / pow(lighting.distance, 2);
	// printf("LIGHT 5\n");
	print_vec(lighting.incident_to_light, "incindent");
	printf("intenns:%f  distnace:%f", lighting.d_intensity, lighting.distance);
	return (lighting);
}

// t_parallel_light	*make_parallel_light_info(t_vec3 dir, t_color intensity, t_dlist **gb_list)
t_parallel_light	*make_parallel_light_info(t_vec3 dir, double intensity, t_dlist **gb_list)
{
	t_parallel_light	*light;

	light = ft_galloc(sizeof(t_parallel_light), gb_list);
	light->d_intensity = intensity;
	light->dir = dir;
	return (light);
}

t_lightsource	*new_light(t_lighttype type, void *light_info, t_dlist **gb_list)
{
	t_lightsource	*light;

	if (light_info == NULL)
		return (NULL);
	light = ft_galloc(sizeof(t_lightsource), gb_list);
	if (light == NULL)
		return (NULL);
	light->type = type;
	light->instance = light_info;
	if (type == L_POINT)
		light->lighting_at = lighting_at_point;
	else
		light->lighting_at = NULL;
	return (light);
}

#ifndef LIGHTSOURCE_H
# define LIGHTSOURCE_H

#include "all.h"

typedef enum e_lighttype{
	// O_AMBIRNT_LIGHT,
	// O_LIGHT,
	L_POINT,
	L_PARALLEL,
} t_lighttype;

typedef struct	s_lighting
{
	double	distance;
	double	d_intensity;
	t_vec3	incident_to_light;
}				t_lighting;

typedef	struct s_light t_lightsource;
struct	s_light
{
	t_lighttype	type;
	void		*instance;
	t_lighting	(*lighting_at)(t_vec3, t_lightsource *);
};

typedef struct	s_point_light
{
	t_vec3		pos;
	// t_color		intensity;
	double		d_intensity;
}				t_point_light;

typedef struct	s_parallel_light
{
	t_vec3		dir;
	// t_color		intensity;
	double		d_intensity;
}				t_parallel_light;

// light.h
t_vec3	get_light_incident_dir(t_point_light light, t_vec3 p);
t_vec3	get_incident_parallel_light(t_parallel_light light);
// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di);
// double	get_deffsuse_ref(t_point_light light, t_circle cir, t_vec3 point);
// double	get_ref(t_point_light light, t_circle cir, t_vec3 point);
double	get_ref(t_point_light light, t_circle cir, t_ray eye, double t);

t_lightsource	*new_light(t_lighttype type, void *light_info, t_dlist **gb_list);
t_point_light	*make_point_light_info(t_vec3 position, double intensity, t_dlist **gb_list);
// t_point_light	*make_point_light_info(t_vec3 position, t_color intensity, t_dlist **gb_list);
t_parallel_light	*make_parallel_light_info(t_vec3 dir, double intensity, t_dlist **gb_list);
// t_parallel_light	*make_parallel_light_info(t_vec3 dir, t_color intensity, t_dlist **gb_list);
t_lighting	lighting_at_point(t_vec3 position, t_lightsource *light);

#endif

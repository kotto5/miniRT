#ifndef OBJ_H
# define OBJ_H

# include "all.h"


// new_obj.c
// t_obj		*new_obj(t_objtype type, void *obj_info, t_dlist **alloc_list);
t_obj	*new_obj(t_objtype type, t_reflect ref, void *obj_info, t_dlist **alloc_list);
// t_circle	*make_circle_instance(t_vec3 origin, double r, t_reflect ref, t_dlist **gb_list);
// t_plane	*make_plane_instance(t_vec3 vertical, t_reflect ref, t_dlist **gb_list);

t_circle	*make_circle_instance(t_vec3 origin, double r, t_dlist **gb_list);
// t_plane	*make_plane_instance(t_vec3 vertical, t_dlist **gb_list);
t_plane	*make_plane_instance(t_vec3 vertical, t_vec3 point, t_dlist **gb_list);
t_cylinder	*make_cylinder_instance(t_vec3 vertical, t_vec3 point, double r, t_dlist **gb_list);

// t_reflect	get_t_refrect(double am, double di, double sp, double sp_shininess);
// t_reflect	get_t_refrect(t_bright_color am, t_bright_color di, t_bright_color sp, double sp_shininess);
t_reflect	get_t_refrect(t_bright_color am, t_bright_color di, t_bright_color sp, double sp_shininess, bool use_perfect_reflectance, t_bright_color perfect_reflectance);

// sq.c
bool	do_intersect_ray_and_square(t_ray ray, t_square sq);


// cir.c
// double	get_ray_t_to_cir(t_ray ray, t_circle cir);
t_vec3	get_ray_intersect_vec(t_ray ray, double t);
t_vec3	get_ray_intersect_vec_dir(t_ray ray, t_vec3 point);
t_vec3	get_cir_vertical_dir(t_circle cir, t_vec3 surface_p);
// t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj, t_dlist **alloc_list);
// t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj, t_dlist **alloc_list);
t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_plane(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_cylinder(const t_ray ray, const t_obj *obj);

#endif

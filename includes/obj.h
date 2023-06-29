/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:52:35 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 19:13:02 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_H
# define OBJ_H

# include "all.h"

// new_obj.c
t_obj			*new_obj(t_objtype type, t_reflect ref, void *obj_info);
t_sphere		*make_sphere_instance(t_vec3 origin, double r);
t_plane			*make_plane_instance(t_vec3 vertical, t_vec3 point);
t_cylinder		*make_cylinder_instance(t_vec3 vertical, \
										t_vec3 point, \
										double r, \
										double height);
t_rect			*make_rect_instance(t_vec3 bound1, t_vec3 bound2);
// t_cone			*make_cone_instance(t_vec3 center, double r, t_vec3 tip);
t_cone			*make_cone_instance(t_vec3 center, t_vec3 vertical, double r, double h);

// cir.c
t_vec3			get_ray_intersect_vec(t_ray ray, double t);
t_vec3			get_ray_intersect_vec_dir(t_ray ray, t_vec3 point);
t_vec3			get_cir_vertical_dir(t_sphere cir, t_vec3 surface_p);
t_intersection	get_intersection_sphere(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_plane(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_cylinder(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_rect(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_cone(const t_ray ray, const t_obj *obj);

#endif

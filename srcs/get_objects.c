/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/27 13:44:03 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	give_perfect_reflection(t_obj *obj, char *reflectance)
{
	const double	ratio = ft_atof(reflectance);

	obj->ref.use_perfect_reflectance = true;
	obj->ref.perfect_reflectance.t = ratio;
	obj->ref.perfect_reflectance.r = ratio;
	obj->ref.perfect_reflectance.g = ratio;
	obj->ref.perfect_reflectance.b = ratio;
}

void	*get_sphere_node(char **split)
{
	t_vec3					position;
	t_reflect				ref;
	double					r;
	t_sphere				*sphere;
	t_obj					*obj;

	if (get_vec_from_split(split[1], &position) \
		|| get_ref_from_split(split[3], &ref))
		return (NULL);
	if (ft_isdouble(split[2]) == false)
		return (NULL);
	r = ft_atof(split[2]);
	sphere = make_sphere_instance(position, r);
	if (sphere == NULL)
		return (NULL);
	obj = new_obj(O_SPHERE, ref, sphere);
	if (obj == NULL)
		return (NULL);
	if (split[4])
		give_perfect_reflection(obj, split[4]);
	return (ft_dlstnew(obj));
}

void	*get_plane_node(char **split)
{
	t_vec3		position;
	t_vec3		vertical;
	t_reflect	ref;
	t_plane		*plane;
	t_obj		*obj;

	if (get_vec_from_split(split[1], &position) \
		|| get_vec_from_split(split[2], &vertical) \
		|| get_ref_from_split(split[3], &ref))
		return (NULL);
	plane = make_plane_instance(vertical, position);
	if (plane == NULL)
		return (NULL);
	obj = new_obj(O_PLANE, ref, plane);
	if (obj == NULL)
		return (NULL);
	if (split[4])
		give_perfect_reflection(obj, split[4]);
	return (ft_dlstnew(obj));
}

void	*get_cylinder_node(char **split)
{
	t_vec3		position;
	t_vec3		axis;
	t_reflect	ref;
	t_cylinder	*cylinder;
	t_obj		*obj;

	if (get_vec_from_split(split[1], &position) || \
		get_vec_from_split(split[2], &axis) || \
		get_ref_from_split(split[5], &ref) || \
		ft_isdouble(split[4]) == false || \
		ft_isdouble(split[3]) == false)
		return (NULL);
	cylinder = make_cylinder_instance(axis, position, \
		ft_atof(split[3]), ft_atof(split[4]));
	if (cylinder == NULL)
		return (NULL);
	obj = new_obj(O_CYLINDER, ref, cylinder);
	if (obj == NULL)
		return (NULL);
	if (split[6])
		give_perfect_reflection(obj, split[4]);
	return (ft_dlstnew(obj));
}

void	*get_camera(char **split)
{
	t_camera	*camera;
	t_vec3		position;
	t_vec3		orientation;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (ft_isdigit_str(split[3], 0) == false || \
		get_vec_from_split(split[1], &position) || \
		get_vec_from_split(split[2], &orientation))
		return (NULL);
	camera = make_camera(ft_atof(split[3]), position, orientation);
	return (camera);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/03 14:00:49 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*get_ambient_lignt(char **split)
{
	t_bright_color	*am_light;
	t_reflect		ref;
	double			raito;

	if (get_size_double_ptr(split) != 3)
		return (NULL);
	if (ft_isdouble(split[1]) == false \
					|| get_ref_from_split(split[2], &ref))
		return (NULL);
	raito = ft_atof(split[1]);
	am_light = malloc(sizeof(t_bright_color));
	if (am_light == NULL)
		return (NULL);
	*am_light = b_color_mult_constant(ref.am, raito);
	return (am_light);
}

void	*get_spot_light_node(char **split)
{
	t_lightsource	*light;
	t_spot_light	*s_light;
	t_reflect		ref;
	t_vec3			pos;
	t_vec3			orientation;

	set_vec_from_split(split[1], &pos);
	set_vec_from_split(split[2], &orientation);
	get_ref_from_split(split[5], &ref);
	s_light = make_spot_light_info(pos, \
									orientation, \
									ft_atof(split[3]), \
									b_color_mult_constant(ref.am, \
										ft_atof(split[4])));
	if (s_light == NULL)
		return (NULL);
	light = new_light(L_SPOT, s_light);
	if (light == NULL)
		return (NULL);
	return (ft_dlstnew(light));
}

void	*get_light_node(char **split)
{
	t_vec3			pos;
	t_reflect		ref;
	double			raito;
	t_point_light	*p_light;
	t_lightsource	*light;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (ft_isdouble(split[2]) == false || \
		get_ref_from_split(split[3], &ref) || \
		set_vec_from_split(split[1], &pos))
		return (NULL);
	raito = ft_atof(split[2]);
	p_light = make_point_light_info(pos, \
									b_color_mult_constant(ref.am, \
															raito));
	if (p_light == NULL)
		return (NULL);
	light = new_light(L_POINT, p_light);
	if (light == NULL)
		return (NULL);
	return (ft_dlstnew(light));
}

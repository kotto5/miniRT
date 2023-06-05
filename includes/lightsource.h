/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightsource.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 21:51:41 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/05 21:52:23 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTSOURCE_H
# define LIGHTSOURCE_H

# include "all.h"

// light.h
t_vec3				get_light_incident_dir(t_point_light light, t_vec3 p);
t_vec3				get_incident_parallel_light(t_parallel_light light);

t_lightsource		*new_light(t_lighttype type, void *light_info);
t_point_light		*make_point_light_info(t_vec3 position, \
											t_bright_color intensity);
t_parallel_light	*make_parallel_light_info(t_vec3 dir, \
												double intensity, \
												t_dlist **gb_list);
t_lighting			lighting_at_point(t_vec3 position, \
										t_lightsource *light);

// bright_color_clc1.c
unsigned int		to_img_color_from_b_color(t_bright_color *b_color);

t_bright_color		b_color_mult(t_bright_color b1, t_bright_color b2);
t_bright_color		b_color_add(t_bright_color b1, t_bright_color b2);
t_bright_color		b_color_get(double t, double r, double g, double b);
t_bright_color		b_color_mult_constant(t_bright_color b1, double d);

// img_color_clc1.c
t_img_color			img_color_add(t_img_color color1, t_img_color color2);
t_img_color			img_color_mult(t_img_color color, unsigned char k);
t_img_color			get_img_color(unsigned char t, \
									unsigned char r, \
									unsigned char g, \
									unsigned char b);

#endif

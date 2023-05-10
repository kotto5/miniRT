/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_color_clc1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:42 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/27 16:05:16 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_img_color	get_img_color(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	t_img_color	color;

	color.trgb.t = t;
	color.trgb.r = r;
	color.trgb.g = g;
	color.trgb.b = b;
	return (color);
}

t_img_color	img_color_mult(t_img_color color, unsigned char k)
{
	t_img_color	ans;

	ans.color = color.color * k;
	ans.color = color.color * k;
	ans.color = color.color * k;
	return (ans);
}

t_img_color	img_color_add(t_img_color color1, t_img_color color2)
{
	t_img_color	ans;
	int	buf;

	buf = color1.trgb.t + color2.trgb.t;
	if (buf > 0xff)
		buf = 0xff;
	ans.trgb.t = buf;
	buf = color1.trgb.r + color2.trgb.r;
	if (buf > 0xff)
		buf = 0xff;
	ans.trgb.r = buf;
	buf = color1.trgb.g + color2.trgb.g;
	if (buf > 0xff)
		buf = 0xff;
	ans.trgb.g = buf;
	buf = color1.trgb.b + color2.trgb.b;
	if (buf > 0xff)
		buf = 0xff;
	ans.trgb.b = buf;
	return (ans);
}

unsigned int	img_color_mult_ref_incident_constant(t_img_color ref, t_img_color incident, double constant)
{
	t_img_color	color;
	double	buf;

	buf = (double)ref.trgb.t * (double)incident.trgb.t * constant;
	color.trgb.t = buf / 1.0;
	buf = (double)ref.trgb.r * (double)incident.trgb.r * constant;
	color.trgb.r = buf / 1.0;
	buf = (double)ref.trgb.g * (double)incident.trgb.g * constant;
	color.trgb.g = buf / 1.0;
	buf = (double)ref.trgb.b * (double)incident.trgb.b * constant;
	color.trgb.b = buf / 1.0;
	return (color.color);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_color_clc1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:06:42 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/05 17:23:46 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_img_color	get_img_color(unsigned char t, \
							unsigned char r, \
							unsigned char g, \
							unsigned char b)
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
	int			buf;

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

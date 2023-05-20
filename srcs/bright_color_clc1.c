#include "all.h"

t_bright_color	b_color_get(double t, double r, double g, double b)
{
	t_bright_color	b_color;

	b_color.t = t;
	b_color.r = r;
	b_color.g = g;
	b_color.b = b;
	return (b_color);
}

t_bright_color	b_color_add(t_bright_color b1, t_bright_color b2)
{
	t_bright_color	b_color;

	b_color.t = b1.t + b2.t;
	b_color.r = b1.r + b2.r;
	b_color.g = b1.g + b2.g;
	b_color.b = b1.b + b2.b;
	return (b_color);
}

t_bright_color	b_color_mult(t_bright_color b1, t_bright_color b2)
{
	t_bright_color	b_color;

	// b_color.t = b1.t * b2.t;
	// b_color.r = b1.r * b2.r;
	// b_color.g = b1.g * b2.g;
	// b_color.b = b1.b * b2.b;
	double			buf;

	buf = b1.t * b2.t;
	if (buf > 256)
		buf = 256;
	b_color.t = buf;

	buf = b1.r * b2.r;
	if (buf > 256)
		buf = 256;
	b_color.r = buf;
	buf = b1.g * b2.g;
	if (buf > 256)
		buf = 256;
	b_color.g = buf;
	buf = b1.b * b2.b;
	if (buf > 256)
		buf = 256;
	b_color.b = buf;

	return (b_color);
}

t_bright_color	b_color_mult_constant(t_bright_color b1, double d)
{
	t_bright_color	b_color;
	double			buf;

	buf = b1.t * d;
	if (buf > 256)
		buf = 100;
	b_color.t = buf;

	buf = b1.r * d;
	if (buf > 256)
		buf = 100;
	b_color.r = buf;
	buf = b1.g * d;
	if (buf > 256)
		buf = 100;
	b_color.g = buf;
	buf = b1.b * d;
	if (buf > 256)
		buf = 100;
	b_color.b = buf;
	return (b_color);
}

unsigned int	to_img_color_from_b_color(t_bright_color *b_color)
{
	static t_img_color	img_color;

	if (b_color == NULL)
		return (BACK_COLOR);
	if (isnan(b_color->t) || isnan(b_color->r) || isnan(b_color->g) || isnan(b_color->b))
	{
		printf("bright_colorclc.1 to_img_color_from_b_color is nan!!!\n");
	}
	if (b_color->t > 1)
		img_color.trgb.t = 0xff;
	else
		img_color.trgb.t = (b_color->t * 0xff);

	if (b_color->r > 1)
		img_color.trgb.r = 0xff;
	else
		img_color.trgb.r = (b_color->r * 0xff);

	if (b_color->g > 1)
		img_color.trgb.g = 0xff;
	else
		img_color.trgb.g = (b_color->g * 0xff);

	if (b_color->b > 1)
		img_color.trgb.b = 0xff;
	else
		img_color.trgb.b = (b_color->b * 0xff);
	return (img_color.color);
}

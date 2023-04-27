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

	b_color.t = b1.t * b2.t;
	b_color.r = b1.r * b2.r;
	b_color.g = b1.g * b2.g;
	b_color.b = b1.b * b2.b;
	return (b_color);
}

t_bright_color	b_color_mult_constant(t_bright_color b1, double d)
{
	t_bright_color	b_color;

	b_color.t = b1.t * d;
	b_color.r = b1.r * d;
	b_color.g = b1.g * d;
	b_color.b = b1.b * d;
	return (b_color);
}

t_img_color	to_img_color_from_b_color(t_bright_color b_color)
{
	// printf("%f %f %f %f\n", b_color.t, b_color.r, b_color.g, b_color.b);
	t_img_color	img_color;


	if (b_color.t > 1)
		img_color.trgb.t = 0xff;
	else
		img_color.trgb.t = (unsigned char)(b_color.t * 0xff);

	if (b_color.r > 1)
		img_color.trgb.r = 0xff;
	else
		img_color.trgb.r = (unsigned char)(b_color.r * 0xff);

	if (b_color.g > 1)
		img_color.trgb.g = 0xff;
	else
		img_color.trgb.g = (unsigned char)(b_color.g * 0xff);

	if (b_color.b > 1)
		img_color.trgb.b = 0xff;
	else
		img_color.trgb.b = (unsigned char)(b_color.b * 0xff);
	return (img_color);
}

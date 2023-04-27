#ifndef STRUCT_H
#define STRUCT_H

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_trgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}				t_trgb;

typedef union	u_color
{
	t_trgb			trgb;
	unsigned int	color;
}				t_img_color;

#endif

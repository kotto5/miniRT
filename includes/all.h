#ifndef ALL_H
# define ALL_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "libft.h"
#include <math.h>

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
}				t_color;

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}				t_ray;

typedef struct	s_circle
{
	t_vec3	pos;
	double	r;
}				t_circle;


// typedef struct	


typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

int	*make_img(t_img *img);

// #define WIN_WIDTH 1000
// #define WIN_HEIGHT 500
#define WIN_WIDTH 512
#define WIN_HEIGHT 512
#define ERROR 1
#define SUCCESS 0

#endif

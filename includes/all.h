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

// Rr = Ra + Rd + Rs
typedef struct	s_reflect
{
	// 環境光反射係数 ambient
	double	am;
	// 拡散反射係数 diffuse
	double	di;
	// 鏡面反射係数 spqcular
	double	sp;
	// 1 <= shininess ハイライトの鋭さ
	double	sp_shininess;
}				t_reflect;

// 
typedef struct	s_circle
{
	t_reflect	ref;
	t_vec3		pos;
	double		r;
}				t_circle;

// VecP (x, y, z) VecN (a, b, c) が直交
typedef struct	s_square
{
	t_reflect	ref;
	t_vec3		pos;
	t_vec3		n_dir;
}				t_square;

typedef struct	s_point_light
{
	t_vec3		pos;
}				t_point_light;

typedef struct	s_parallel_light
{
	t_vec3		pos;
	t_vec3		dir;
}				t_parallel_light;


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

t_vec3	vec_add(t_vec3 va, t_vec3 vb);
t_vec3	vec_sub(t_vec3 va, t_vec3 vb);
t_vec3	vec_mult(t_vec3 va, double k);
double	vec_dot(t_vec3 va, t_vec3 vb);
t_vec3	vec_cross(t_vec3 va, t_vec3 vb);
double	vec_mag_sq(t_vec3 va);
double	vec_mag(t_vec3 va);
void	set_vec3(t_vec3 *vec, double x, double y, double z);

t_vec3	get_incident_point_light(t_point_light light, t_vec3 p);
t_vec3	get_incident_parallel_light(t_parallel_light light);

// 関数ポインタ使って、クラスっぽいこと実現しよう
// square.n() 的な


#endif

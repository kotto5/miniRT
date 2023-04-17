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
	double		power;
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

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_ray	eye;
}				t_env;

int	*make_img(t_img *img);
int	*make_img2(t_img *img, t_ray eye);

// #define WIN_WIDTH 1000
// #define WIN_HEIGHT 500
#define WIN_WIDTH 512
#define WIN_HEIGHT 512
#define ERROR 1
#define SUCCESS 0

enum{
	ALLOW_LEFT = 123,
	ALLOW_RIGHT = 124,
	ALLOW_DOWN = 125,
	ALLOW_UP = 126,
};

t_vec3	vec_add(t_vec3 va, t_vec3 vb);
t_vec3	vec_sub(t_vec3 va, t_vec3 vb);
t_vec3	vec_mult(t_vec3 va, double k);
double	vec_dot(t_vec3 va, t_vec3 vb);
t_vec3	vec_cross(t_vec3 va, t_vec3 vb);
double	vec_mag_sq(t_vec3 va);
double	vec_mag(t_vec3 va);
void	set_vec3(t_vec3 *vec, double x, double y, double z);

// light.h
t_vec3	get_incident_point_light(t_point_light light, t_vec3 p);
t_vec3	get_incident_parallel_light(t_parallel_light light);
// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di);
double	get_deffsuse_ref(t_point_light light, t_circle cir, t_vec3 point);
// double	get_ref(t_point_light light, t_circle cir, t_vec3 point);
double	get_ref(t_point_light light, t_circle cir, t_ray eye, double t);

// cir.c
double	get_ray_t_to_cir(t_ray ray, t_circle cir);
t_vec3	get_intersect_point_ray_cir(t_ray ray, double t);
t_vec3	get_normal_cir(t_circle cir, t_vec3 surface_p);

// utils.c
void	mlx_put_to_img(t_img *data, int x, int y, int color);
// t_vec3	convert_vecter_to_window_from_imgvec(int x, int y);
t_vec3	convert_vecter_to_window_from_imgvec(int x, int y, t_ray eye);


// sq.c
bool	do_intersect_ray_and_square(t_ray ray, t_square sq);

// 関数ポインタ使って、クラスっぽいこと実現しよう
// square.n() 的な


#endif

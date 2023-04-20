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

// little endian
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


typedef	struct s_circle t_circle;

struct	s_circle
{
	t_reflect	ref;
	t_vec3		pos;
	double		r;
	t_vec3		(*vertical)(t_circle, t_vec3);
};

// typedef struct	s_circle
// {
// 	t_reflect	ref;
// 	t_vec3		pos;
// 	double		r;
// 	t_vec3		(*vertical)(t_circle, t_vec3);
// }				t_circle;

// VecP (x, y, z) VecN (a, b, c) が直交
typedef struct	s_square
{
	t_reflect	ref;
	t_vec3		pos;
	t_vec3		n_dir;
}				t_square;

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

typedef struct	s_intersection
{
	bool	does_intersect;
	double	distance;
	t_vec3	position;
	t_vec3	vertical_dir;
}				t_intersection;

typedef enum e_objtype{
	O_AMBIRNT_LIGHT = 1,
	O_LIGHT,
	O_CAMERA,
	O_SPHERE,
	O_PLANE,
	O_CYLINDER,
	O_CIRCLE,
} t_objtype;

typedef enum e_lighttype{
	O_AMBIRNT_LIGHT,
	O_LIGHT,
} t_lighttype;

typedef struct	s_circle_info
{
	t_reflect	ref;
	t_vec3		pos;
	t_vec3		n_dir;
}				t_circle_info;

typedef	struct s_obj t_obj;
struct	s_obj
{
	t_objtype	type;
	void		*instance;
	t_intersection		(*get_intersection)(const t_ray, const t_obj *);
};

typedef struct	s_lighting
{
	double	distance;
	t_color	intensity;
	t_vec3	vecter;
}				t_lighting;

typedef	struct s_light t_light;
struct	s_light
{
	t_lighttype	type;
	void		*instance;
	t_lighting	(*lighting_at)(t_vec3, t_light);
};

typedef struct	s_point_light
{
	t_vec3		pos;
	t_color		intensity;
}				t_point_light;

typedef struct	s_parallel_light
{
	t_vec3		dir;
	t_color		intensity;
}				t_parallel_light;

int	*make_img(t_img *img);
int	*make_img2(t_img *img, t_ray eye);
int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list);

// #define WIN_WIDTH 1000
// #define WIN_HEIGHT 500
#define WIN_WIDTH 512
#define WIN_HEIGHT 512
#define ERROR 1
#define SUCCESS 0
#define BACK_COLOR 0x0

enum{
	ALLOW_LEFT = 123,
	ALLOW_RIGHT = 124,
	ALLOW_DOWN = 125,
	ALLOW_UP = 126,
};

void	set_vec3(t_vec3 *vec, double x, double y, double z);
t_vec3	vec_add(t_vec3 va, t_vec3 vb);
t_vec3	vec_sub(t_vec3 va, t_vec3 vb);
t_vec3	vec_mult(t_vec3 va, double k);
double	vec_dot(t_vec3 va, t_vec3 vb);
t_vec3	vec_cross(t_vec3 va, t_vec3 vb);
double	vec_mag_sq(t_vec3 va);
double	vec_mag(t_vec3 va);
t_vec3	vec_normilize(t_vec3 vec);
void	print_vec(t_vec3 vec, char *str);
t_vec3	get_vec(double x, double y, double z);

t_obj	*new_obj(t_objtype type, void *obj_info, t_dlist **alloc_list);



// light.h
t_vec3	get_light_incident_dir(t_point_light light, t_vec3 p);
t_vec3	get_incident_parallel_light(t_parallel_light light);
// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di);
double	get_deffsuse_ref(t_point_light light, t_circle cir, t_vec3 point);
// double	get_ref(t_point_light light, t_circle cir, t_vec3 point);
double	get_ref(t_point_light light, t_circle cir, t_ray eye, double t);

// cir.c
double	get_ray_t_to_cir(t_ray ray, t_circle cir);
t_vec3	get_ray_intersect_vec(t_ray ray, double t);
t_vec3	get_ray_intersect_vec_dir(t_ray ray, t_vec3 point);
t_vec3	get_cir_vertical_dir(t_circle cir, t_vec3 surface_p);
// t_intersection	get_circle_intersection(const t_ray ray, const t_obj *obj, t_dlist **alloc_list);
// t_intersection	get_circle_intersection(const t_ray ray, const t_obj *obj, t_dlist **alloc_list);
t_intersection	get_circle_intersection(const t_ray ray, const t_obj *obj);


// utils.c
void	mlx_put_to_img(t_img *data, int x, int y, int color);
// t_vec3	get_screen_vec(int x, int y);
t_vec3	get_screen_vec(int x, int y, t_ray eye);


// sq.c
bool	do_intersect_ray_and_square(t_ray ray, t_square sq);

// 関数ポインタ使って、クラスっぽいこと実現しよう
// square.n() 的な


#endif

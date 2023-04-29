#ifndef STRUCT_H
#define STRUCT_H

#include "all.h"

typedef	struct	s_obj t_obj;
typedef struct	s_intersection t_intersection;

// little endian
typedef struct	s_trgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}				t_trgb;

typedef union	u_img_color
{
	t_trgb			trgb;
	unsigned int	color;
}				t_img_color;

typedef struct	s_bright_color
{
	double	t;
	double	r;
	double	g;
	double	b;
}				t_bright_color;

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
	t_dlist	*gb_list;
}				t_env;

typedef struct	s_scene
{
	t_dlist	*obj_list;
	t_dlist	*light_list;
	double	ambient_intensity;
	// t_intersection	get_nearest_intersection(*t_scene, t_ray);
}				t_scene;





// Rr = Ra + Rd + Rs
typedef struct	s_reflect
{
	// 環境光反射係数 ambient
	t_bright_color	am;
	// 拡散反射係数 diffuse
	t_bright_color	di;
	// 鏡面反射係数 spqcular
	t_bright_color	sp;
	// 1 <= shininess ハイライトの鋭さ
	double			sp_shininess;

	// 完全鏡面反射　使うか
	bool			use_perfect_reflectance;
	t_bright_color	perfect_reflectance;
}				t_reflect;

typedef	struct s_circle t_circle;
struct	s_circle
{
	// t_reflect	ref;
	t_vec3		pos;
	double		r;
	t_vec3		(*vertical)(t_circle, t_vec3);
};

// VecP (x, y, z) VecN (a, b, c) が直交
typedef struct	s_square
{
	// t_reflect	ref;
	t_vec3		pos;
	t_vec3		n_dir;
}				t_square;

typedef struct	s_plane
{
	// t_reflect	ref;
	t_vec3		position;
	t_vec3		vertical;
}				t_plane;

typedef enum e_objtype{
	O_CAMERA,
	O_SPHERE,
	O_PLANE,
	O_CYLINDER,
	O_CIRCLE,
} t_objtype;

struct	s_intersection
{
	bool	does_intersect;
	double	distance;
	t_vec3	position;
	t_vec3	vertical_dir;
};

typedef struct	s_circle_info
{
	t_reflect	ref;
	t_vec3		pos;
	t_vec3		n_dir;
}				t_circle_info;

struct	s_obj
{
	t_reflect	ref;
	t_objtype	type;
	void		*instance;
	t_intersection		(*get_intersection)(const t_ray, const t_obj *);
};






typedef enum e_lighttype{
	// O_AMBIRNT_LIGHT,
	// O_LIGHT,
	L_POINT,
	L_PARALLEL,
} t_lighttype;

typedef struct	s_lighting
{
	double	distance;
	// double	d_intensity;
	t_bright_color	intensity;
	t_vec3	incident_to_light;
}				t_lighting;

typedef	struct s_light t_lightsource;
struct	s_light
{
	t_lighttype	type;
	void		*instance;
	t_lighting	(*lighting_at)(t_vec3, t_lightsource *);
};

typedef struct	s_point_light
{
	t_vec3		pos;
	// t_img_color		intensity;
	t_bright_color	intensity;
	// double		d_intensity;
}				t_point_light;

typedef struct	s_parallel_light
{
	t_vec3		dir;
	// t_img_color		intensity;
	// double		d_intensity;
}				t_parallel_light;

typedef struct	s_intersion_info
{
	t_obj	*obj;
	t_intersection intersection;
}				t_intersection_info;



#endif

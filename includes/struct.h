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

typedef struct	s_mat3{
	double	m[3][3];
}				t_mat3;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
	double	distance_to_window;
	t_vec3	orientation;
	t_mat3	rotation;
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
	t_ray	*eye;
	t_dlist	*obj_list;
	t_dlist	*light_list;
	t_dlist	*gb_list;
	t_dtree	*obj_tree;
	t_bright_color	*am_light;
}				t_env;

typedef struct	s_scene
{
	t_dlist			*obj_list;
	t_dlist			*light_list;
	t_bright_color	*am_light;
	t_dtree			*obj_tree;
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
	t_vec3		pos;
	double		r;
};

typedef struct	s_plane
{
	t_vec3		position;
	t_vec3		vertical;
}				t_plane;

typedef struct	s_rect
{
	t_vec3		bound1;
	t_vec3		bound2;
}				t_rect;

typedef struct	s_cylinder
{
	double		r;
	t_vec3		position;
	t_vec3		vertical;
}				t_cylinder;

typedef enum e_objtype{
	O_CIRCLE,
	O_SPHERE,
	O_PLANE,
	O_CYLINDER,
	O_RECT,
} t_objtype;

struct	s_intersection
{
	bool	does_intersect;
	bool	is_inside;
	double	distance;
	t_vec3	position;
	t_vec3	vertical_dir;
};

struct	s_obj
{
	t_objtype	type;
	void		*instance;

	t_reflect	ref;
	t_intersection		(*get_intersection)(const t_ray, const t_obj *);
};

typedef enum e_lighttype{
	// O_LIGHT,
	L_POINT,
	L_PARALLEL,
} t_lighttype;

typedef struct	s_lighting
{
	double	distance;
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
	t_vec3			pos;
	t_bright_color	intensity;
}				t_point_light;

typedef struct	s_parallel_light
{
	t_vec3		dir;
	// t_img_color		intensity;
}				t_parallel_light;

typedef struct	s_intersion_info
{
	t_obj	*obj;
	t_intersection intersection;
}				t_intersection_info;



#endif

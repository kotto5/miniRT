#ifndef OBJ_H
# define OBJ_H

# include "all.h"

// Rr = Ra + Rd + Rs
typedef struct	s_reflect
{
	// 環境光反射係数 ambient
	// double	d_am;
	t_bright_color	am;
	// 拡散反射係数 diffuse
	// double	d_di;
	t_bright_color	di;
	// 鏡面反射係数 spqcular
	// double	d_sp;
	t_bright_color	sp;
	// 1 <= shininess ハイライトの鋭さ
	double	sp_shininess;
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
	t_vec3		vertical;
}				t_plane;

typedef enum e_objtype{
	O_CAMERA,
	O_SPHERE,
	O_PLANE,
	O_CYLINDER,
	O_CIRCLE,
} t_objtype;

typedef struct	s_intersection
{
	bool	does_intersect;
	double	distance;
	t_vec3	position;
	t_vec3	vertical_dir;
}				t_intersection;


typedef struct	s_circle_info
{
	t_reflect	ref;
	t_vec3		pos;
	t_vec3		n_dir;
}				t_circle_info;

typedef	struct s_obj t_obj;
struct	s_obj
{
	t_reflect	ref;
	t_objtype	type;
	void		*instance;
	t_intersection		(*get_intersection)(const t_ray, const t_obj *);
};

// new_obj.c
// t_obj		*new_obj(t_objtype type, void *obj_info, t_dlist **alloc_list);
t_obj	*new_obj(t_objtype type, t_reflect ref, void *obj_info, t_dlist **alloc_list);
// t_circle	*make_circle_instance(t_vec3 origin, double r, t_reflect ref, t_dlist **gb_list);
// t_plane	*make_plane_instance(t_vec3 vertical, t_reflect ref, t_dlist **gb_list);

t_circle	*make_circle_instance(t_vec3 origin, double r, t_dlist **gb_list);
t_plane	*make_plane_instance(t_vec3 vertical, t_dlist **gb_list);

// t_reflect	get_t_refrect(double am, double di, double sp, double sp_shininess);
t_reflect	get_t_refrect(t_bright_color am, t_bright_color di, t_bright_color sp, double sp_shininess);

// sq.c
bool	do_intersect_ray_and_square(t_ray ray, t_square sq);


// cir.c
// double	get_ray_t_to_cir(t_ray ray, t_circle cir);
t_vec3	get_ray_intersect_vec(t_ray ray, double t);
t_vec3	get_ray_intersect_vec_dir(t_ray ray, t_vec3 point);
t_vec3	get_cir_vertical_dir(t_circle cir, t_vec3 surface_p);
// t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj, t_dlist **alloc_list);
// t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj, t_dlist **alloc_list);
t_intersection	get_intersection_circle(const t_ray ray, const t_obj *obj);
t_intersection	get_intersection_plane(const t_ray ray, const t_obj *obj);

#endif

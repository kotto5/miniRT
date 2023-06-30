/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:24:49 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/30 23:33:06 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "all.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}				t_vec3;

typedef struct s_intersection
{
	bool	does_intersect;
	bool	is_inside;
	double	distance;
	t_vec3	position;
	t_vec3	vertical_dir;
}		t_intersection;

typedef struct s_mat3{
	double	m[3][3];
}				t_mat3;

typedef struct s_ray
{
	t_vec3	pos;
	t_vec3	dir;
	double	distance_to_window;
	t_vec3	orientation;
	t_mat3	rotation;
}				t_ray;

typedef enum e_objtype{
	O_SPHERE,
	O_PLANE,
	O_CYLINDER,
	O_RECT,
	O_CONE,
}			t_objtype;

typedef struct s_bright_color
{
	double	t;
	double	r;
	double	g;
	double	b;
}				t_bright_color;

// Rr = Ra + Rd + Rs
// 環境光反射係数 ambient
// t_bright_color	am;
// 拡散反射係数 diffuse
// t_bright_color	di;
// 鏡面反射係数 spqcular
// t_bright_color	sp;
// 1 <= shininess ハイライトの鋭さ
// 完全鏡面反射　使うか
typedef struct s_reflect
{
	t_bright_color	am;
	t_bright_color	di;
	t_bright_color	sp;
	double			sp_shininess;
	bool			use_perfect_reflectance;
	t_bright_color	perfect_reflectance;
}				t_reflect;

struct					s_obj;
typedef t_intersection	(*t_f_get_intersection)\
							(const struct s_ray, const struct s_obj*);
typedef bool			(*t_f_is_inside_point)(const struct s_obj *obj, \
							const struct s_vec3 point);

typedef struct s_obj
{
	t_objtype				type;
	void					*instance;
	t_reflect				ref;
	t_f_get_intersection	get_intersection;
	t_f_is_inside_point		is_inside_point;
	bool					is_closed;
}				t_obj;

// little endian
typedef struct s_trgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	t;
}				t_trgb;

typedef union u_img_color
{
	t_trgb			trgb;
	unsigned int	color;
}				t_img_color;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	higher_left_corner;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	orientation;
	t_vec3	rotation_axis;
	double	rotation_radian;
	double	fov;
}				t_camera;

typedef struct s_env
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_ray			eye;
	t_dlist			*obj_list;
	t_dlist			*light_list;
	t_dlist			*gb_list;
	t_dtree			*obj_tree;
	t_bright_color	*am_light;
	t_camera		*camera;
}				t_env;

typedef struct s_scene
{
	t_dlist			*obj_list;
	t_dlist			*light_list;
	t_bright_color	*am_light;
	t_dtree			*obj_tree;
}				t_scene;

typedef struct s_sphere
{
	t_vec3		pos;
	double		r;
}		t_sphere;

typedef struct s_plane
{
	t_vec3		position;
	t_vec3		vertical;
}				t_plane;

typedef struct s_rect
{
	t_vec3		bound1;
	t_vec3		bound2;
}				t_rect;

typedef struct s_cylinder
{
	double		r;
	t_vec3		position;
	t_vec3		vertical;
	double		height;
}				t_cylinder;

typedef struct s_cone
{
	t_vec3		center;
	double		r;
	t_vec3		tip;
}				t_cone;

typedef enum e_lighttype{
	L_POINT,
	L_PARALLEL,
	L_SPOT,
}				t_lighttype;

typedef struct s_lighting
{
	double			distance;
	t_bright_color	intensity;
	t_vec3			incident_to_light;
}				t_lighting;

typedef struct s_lightsource
{
	t_lighttype			type;
	void				*instance;
	struct s_lighting	(*lighting_at)\
							(struct s_vec3 vec, struct s_lightsource *light);
}				t_lightsource;

typedef struct s_point_light
{
	t_vec3			pos;
	t_bright_color	intensity;
}				t_point_light;

typedef struct s_spot_light
{
	t_vec3			pos;
	t_vec3			orientation;
	double			apex_angle;
	t_bright_color	intensity;
}				t_spot_light;

typedef struct s_parallel_light
{
	t_vec3	dir;
}				t_parallel_light;

typedef struct s_intersion_info
{
	t_obj			*obj;
	t_intersection	intersection;
}				t_intersection_info;

typedef struct s_rt
{
	t_bright_color	perfect_reflectance;
	int				depth;
}				t_rt;

typedef struct s_data
{
	t_scene				*scene;
	t_intersection_info	*info;
	t_lightsource		*light;
	t_ray				*ray;
}				t_data;

#endif

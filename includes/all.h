#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <limits.h>
# include "libft.h"
# include "struct.h"
# include "mlx.h"
# include "obj.h"
# include "lightsource.h"

int	*make_img6(t_env *env);

#define WIN_WIDTH 1500
#define WIN_HEIGHT 800
#define WIN_ORD 200

// #define WIN_WIDTH 1800
// #define WIN_HEIGHT 1200

// # define WIN_WIDTH 712
// # define WIN_HEIGHT 512
# define ERROR 1
# define SUCCESS 0
// # define BACK_COLOR 100*256*256+149*256+237
// # define BACK_COLOR 0x00faa9fe
# define BACK_COLOR 0x00ffffff

// if uset os is mac, use this key code
#ifdef __APPLE__
// mac
enum{
	ALLOW_LEFT = 123,
	ALLOW_RIGHT = 124,
	ALLOW_DOWN = 125,
	ALLOW_UP = 126,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_ESC = 53,
};

#elif __linux__
// linux
enum{
	ALLOW_LEFT = 65361,
	ALLOW_RIGHT = 65363,
	ALLOW_DOWN = 65364,
	ALLOW_UP = 65362,
	KEY_Z = 122,
	KEY_X = 120,
	KEY_ESC = 65307,
};

#endif

typedef enum e_event
{
	E_KEY_PRESS = 2,
	E_KEY_RELEASE = 3,
	E_BORRON_PRESS = 4,
	E_BORRON_RELEASE = 5,
	E_MOTION_NOTIFY = 6,
	E_ENTER_NOTIFY = 7,
	E_LEAVE_NOTIFY = 8,
	E_FOCUS_IN = 9,
	E_FOCUS_OUT = 10,
	E_KEYMAP_NOTIFY = 11,
	E_EXPOSE = 12,
	E_GRAPHICS_EXPOSE = 13,
	E_NO_EXPOSE = 14,
	E_VISIBILITY_NOTIFY = 15,
	E_CREATE_NOTIFY = 16,
	E_DESTROY_NOTIFY = 17,
	E_UNMAP_NOTIFY = 18,
	E_MAP_NOTIFY = 19,
	E_MAP_REQUEST = 20,
	E_REPARENT_NOTIFY = 21,
	E_CONFIGURE_NOTIFY = 22,
	E_CONFIGURE_REQUEST = 23,
	E_GRAVITY_NOTIFY = 24,
	E_RESIZE_REQUEST = 25,
	E_CIRCULATE_NOTIFY = 26,
	E_CIRCULATE_REQUEST = 27,
	E_PROPERTY_NOTIFY = 28,
	E_SELECTION_CLEAR = 29,
	E_SELECTION_REQUEST = 30,
	E_SELECTION_NOTIFY = 31,
	E_COLORMAP_NOTIFY = 32,
	E_CLIENT_MESSAGE = 33,
	E_MAPPING_NOTIFY = 34,
	E_GENERIC_EVENT = 35,
	E_LAST_EVENT = 36,
}	t_event;

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
double	constrain(double v, double vmin, double vmax);
double	map(double v, double vmin, double vmax, double tmin, double tmax); // 値のマッピング
t_dlist	*get_obj_list(t_dlist **gb_list);

void	set_event(t_env *env);

// t_img_color	get_img_color(double t, double r, double g, double b);
// t_img_color	color_mult(t_img_color color, double k);
// t_img_color	color_add(t_img_color color1, t_img_color color2);


// utils.c
void	mlx_put_to_img(t_img *data, int x, int y, int color);
// t_vec3	get_screen_vec(int x, int y);
t_vec3	get_screen_vec(int x, int y, t_ray eye);
double	get_distance_to_window(int fov);

// 関数ポインタ使って、クラスっぽいこと実現しよう
// square.n() 的な


#endif

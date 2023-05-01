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


int	*make_img(t_img *img);
int	*make_img2(t_img *img, t_ray eye);
int	*make_img3(t_img *img, t_ray eye, t_dlist **gb_list);

#define WIN_WIDTH 1500
#define WIN_HEIGHT 800

// #define WIN_WIDTH 1800
// #define WIN_HEIGHT 1200

// # define WIN_WIDTH 712
// # define WIN_HEIGHT 512
# define ERROR 1
# define SUCCESS 0
// # define BACK_COLOR 100*256*256+149*256+237
// # define BACK_COLOR 0x00faa9fe
# define BACK_COLOR 0x00ffffff

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
double	constrain(double v, double vmin, double vmax);
double	map(double v, double vmin, double vmax, double tmin, double tmax); // 値のマッピング
t_dlist	*get_obj_list(t_dlist **gb_list);

// t_img_color	get_img_color(double t, double r, double g, double b);
// t_img_color	color_mult(t_img_color color, double k);
// t_img_color	color_add(t_img_color color1, t_img_color color2);


// utils.c
void	mlx_put_to_img(t_img *data, int x, int y, int color);
// t_vec3	get_screen_vec(int x, int y);
t_vec3	get_screen_vec(int x, int y, t_ray eye);

// 関数ポインタ使って、クラスっぽいこと実現しよう
// square.n() 的な


#endif

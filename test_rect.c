#include "all.h"

int	*test_rect(t_env *env)
{
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &env->img.endian);

	t_vec3			vec_win;
	t_img_color		color;
	t_intersection	info;
	t_scene			scene;
	t_obj			*obj;

	scene.obj_list = env->obj_list;
	scene.light_list = get_light_list(&env->gb_list);
	obj = scene.obj_list->content;
	int	x;
	int	y = 0;
	// t_dlist	*node;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			vec_win = get_screen_vec(x, y, env->eye);
			env->eye.dir = vec_normilize(vec_sub(vec_win, env->eye.pos));
			info = obj->get_intersection(env->eye, obj);
			// info = get_nearest_intersection(&scene, &env->eye);
			if (info.does_intersect)
				color.color = 0xffa0ff;
			else
				color.color = BACK_COLOR;
			mlx_put_to_img(&env->img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (NULL);
}




// 1 木構造を操作する関数
//  操作
// オブジェクト分割で
//  ラベリングの方法
// 	2 手動で初期化　動かす
// 	3 最適化する




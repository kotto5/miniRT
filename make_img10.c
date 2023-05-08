#include "all.h"

#define EPSILON 0.001

t_intersection_info	*get_nearest_intersection(t_scene *scene, t_ray *ray)
{
	t_dlist			*node;
	t_obj			*obj_content;
	t_intersection	tmp;
	t_intersection_info	*info;

	info = malloc(sizeof(t_intersection_info));
	ft_memset(info, 0, sizeof(t_intersection_info));
	node = scene->obj_list;
	info->intersection.does_intersect = false;
	while (node)
	{
		obj_content = node->content;
		tmp = obj_content->get_intersection(*ray, obj_content);
		if (tmp.does_intersect && (info->intersection.does_intersect == false || tmp.distance < info->intersection.distance))
		{
			info->intersection = tmp;
			info->obj = obj_content;
		}
		node = node->next;
	}
	return (info);
}

t_bright_color	*ray_trace(t_scene *scene, t_ray *ray);

t_bright_color	*ray_trace_ref(t_scene *scene, t_ray *ray, size_t times)
{
	t_bright_color		*b_color;
	t_intersection_info	*info;
	t_dlist				*node;

	if (times > 4)
		return (NULL);
	b_color = NULL;
	info = get_nearest_intersection(scene, ray);
	if (info->intersection.does_intersect)
	{
		b_color = ft_calloc(sizeof(t_bright_color), 1);
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, get_color_with_at(scene, info, node->content, ray));
			// *b_color = b_color_add(*b_color, get_color_with_at(*ray, info->intersection, node->content, info->obj));
			node = node->next;
		}
		if (info->obj->ref.use_perfect_reflectance)
		{
			t_ray			re_ray;
			t_bright_color	*ret;
			t_vec3			v;
			t_vec3			v2;
			double			dot_product;
			v = vec_mult(ray->dir, -1);
			v2 = vec_normilize(info->intersection.vertical_dir);
			dot_product = vec_dot(v2, v);
			if (dot_product < 0.0)
				return (b_color);
			re_ray.dir = vec_sub(vec_mult(v2, 2.0 * dot_product), v);
			re_ray.pos = vec_add(info->intersection.position, vec_mult(re_ray.dir, EPSILON));
			ret = ray_trace_ref(scene, &re_ray, times + 1);
			if (ret)
			{
				*ret = b_color_mult(*ret, info->obj->ref.perfect_reflectance);
				*b_color = b_color_add(*b_color, *ret);
			}
		}
	}
	return (b_color);
}

t_bright_color	*ray_trace(t_scene *scene, t_ray *ray)
{
	t_bright_color		*b_color;
	t_intersection_info	*info;
	t_dlist				*node;

	b_color = NULL;
	info = get_nearest_intersection(scene, ray);
	if (info->intersection.does_intersect)
	{
		b_color = ft_calloc(sizeof(t_bright_color), 1);
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, get_color_with_at(scene, info, node->content, ray));
			// *b_color = b_color_add(*b_color, get_color_with_at(*ray, info->intersection, node->content, info->obj));
			node = node->next;
		}
		if (info->obj->ref.use_perfect_reflectance)
		{
			t_ray			re_ray;
			t_bright_color	*ret;
			t_vec3			v;
			t_vec3			v2;
			double			dot_product;
			v = vec_mult(ray->dir, -1);
			v2 = vec_normilize(info->intersection.vertical_dir);
			dot_product = vec_dot(v2, v);
			if (dot_product < 0.0)
				return (b_color);
			re_ray.dir = vec_sub(vec_mult(v2, 2.0 * dot_product), v);
			re_ray.pos = vec_add(info->intersection.position, vec_mult(re_ray.dir, EPSILON));
			ret = ray_trace_ref(scene, &re_ray, 0);
			if (ret)
			{
				*ret = b_color_mult(*ret, info->obj->ref.perfect_reflectance);
				*b_color = b_color_add(*b_color, *ret);
			}
		}
	}
	return (b_color);
}

// int	*make_img6(t_img *img, t_ray eye, t_dlist **gb_list)
int	*make_img6(t_env *env)
{
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bits_per_pixel, &env->img.line_length, &env->img.endian);

	t_vec3			vec_win;
	t_img_color		color;
	t_bright_color	*ref_color;

	t_scene			scene;
	scene.obj_list = env->obj_list;
	scene.light_list = env->light_list;

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
			ref_color = ray_trace(&scene, &env->eye);
			if (ref_color == NULL)
				color.color = BACK_COLOR;
			else
				color = to_img_color_from_b_color(*ref_color);
			mlx_put_to_img(&env->img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (NULL);
}

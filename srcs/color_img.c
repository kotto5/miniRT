#include <sys/time.h>
#include "all.h"

int	get_nearest_intersection(t_intersection_info *info, t_scene *scene, t_ray *ray)
{
	t_dlist			*node;
	t_obj			*obj_content;
	t_intersection	tmp;

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
	return (SUCCESS);
}

t_bright_color	*ray_trace(t_bright_color *b_color, t_scene *scene, t_ray *ray);

t_bright_color	*ray_trace_ref(t_scene *scene, t_ray *ray, size_t times)
{
	t_bright_color		*b_color;
	t_intersection_info	info;
	t_dlist				*node;

	if (times > 6)
		return (NULL);
	b_color = NULL;
	get_nearest_intersection(&info, scene, ray);
	if (info.intersection.does_intersect)
	{
		b_color = ft_calloc(sizeof(t_bright_color), 1);
		*b_color = b_color_mult(info.obj->ref.am, *scene->am_light);
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, get_color_with_at(scene, &info, node->content, ray));
			node = node->next;
		}
		if (info.obj->ref.use_perfect_reflectance)
		{
			t_ray			re_ray;
			t_bright_color	*ret;
			t_vec3			v;
			t_vec3			v2;
			double			dot_product;
			v = vec_mult(ray->dir, -1);
			v2 = vec_normalize(info.intersection.vertical_dir);
			dot_product = vec_dot(v2, v);
			if (dot_product < 0.0)
				return (b_color);
			re_ray.dir = vec_sub(vec_mult(v2, 2.0 * dot_product), v);
			re_ray.pos = vec_add(info.intersection.position, vec_mult(re_ray.dir, EPSILON));
			ret = ray_trace_ref(scene, &re_ray, times + 1);
			if (ret)
			{
				*ret = b_color_mult(*ret, info.obj->ref.perfect_reflectance);
				*b_color = b_color_add(*b_color, *ret);
			}
		}
	}
	return (b_color);
}

t_bright_color	*ray_trace(t_bright_color *b_color, t_scene *scene, t_ray *ray)
{
	t_intersection_info	info;
	t_dlist				*node;

	ft_memset(b_color, 0, sizeof(t_bright_color));
	get_nearest_intersection(&info, scene, ray);
	if (info.intersection.does_intersect)
	{
		node = scene->light_list;
		while (node)
		{
			*b_color = b_color_add(*b_color, get_color_with_at(scene, &info, node->content, ray));
			node = node->next;
		}
	}
	return (b_color);
}

static void	print_time(int a)
{
	static long		before;
	static long		now;
	struct timeval	t1;
	long			s_time;

	if (gettimeofday(&t1, NULL))
		return ;
	s_time = (long)(t1.tv_sec);
	now = s_time * 10000000 + (long)(t1.tv_usec);
	if (before == 0)
		printf("[%d]time %d\n", a, 0);
	else
		printf("[%d]time %ld\n", a, now - before);
	before = now;
}

int	color_img(t_env *env)
{
	t_bright_color	ref_color;
	t_scene			scene;
	int	x = 0;
	int	y = 0;

	scene.obj_list = env->obj_list;
	scene.light_list = env->light_list;
	scene.am_light = env->am_light;

	print_time(3);
	env->eye = malloc(sizeof(t_ray));
	env->eye->pos = get_vec(0, 0, 0);
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			env->eye = get_ray(env->camera, x, y);
			ray_trace(&ref_color, &scene, env->eye);
			mlx_put_to_img(&env->img, x, y, to_img_color_from_b_color(&ref_color));
			x++;
		}
		y++;
	}
	print_time(4);
	return (SUCCESS);
}

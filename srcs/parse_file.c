#include "all.h"

#define SYNTAX 3
#define OPEN_ERROR 2
#define CLOSE_ERROR 4

// size_t	get_size_double_ptr(void **ptr) これで怒られるのなんで？
size_t	get_size_double_ptr(char **ptr)
{
	size_t	len;

	len = 0;
	if (!ptr)
		return (0);
	while (ptr[len])
		len++;
	return (len);
}

void	print_argv(char **argv)
{
	(void)argv;
	// size_t	i = 0;

	// printf("===== print argv =======\n");
	// if (argv == NULL)
	// 	printf("ARG is NULL!\n");
	// while (argv[i])
	// 	printf("[%s]:", argv[i++]);
	// printf(" size[%ld] \n============\n", i);
}

void	free_double_ptr(char **ptr){
	size_t	i;
	// char	*buf;

	if (ptr == NULL)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free (ptr);
}

int split_to_vec3(char **split_tmp, t_vec3 *position)
{
	position->x = atof(split_tmp[0]);
	position->y = atof(split_tmp[1]);
	position->z = atof(split_tmp[2]);
	return (SUCCESS);
}

int get_vec_from_split(char *str, t_vec3 *vec)
{
	char	**split_tmp;

	split_tmp = ft_split(str, ',');
	print_argv(split_tmp);
	if (get_size_double_ptr(split_tmp) != 3 || ft_isdouble(split_tmp[0]) == false ||
		ft_isdouble(split_tmp[1]) == false || ft_isdouble(split_tmp[2]) == false)
	{
		// printf("%d %d %d\n", ft_isdouble(split_tmp[0]),ft_isdouble(split_tmp[1]),ft_isdouble(split_tmp[2]));
		// printf("%s/ %s/ %s/\n", split_tmp[0],split_tmp[1],split_tmp[2]);
		free_double_ptr(split_tmp);
		return (ERROR);
	}
	vec->x = ft_atof(split_tmp[0]);
	vec->y = ft_atof(split_tmp[1]);
	vec->z = ft_atof(split_tmp[2]);
	// printf("x[%f], y[%f], z[%f]\n", vec->x, vec->y, vec->z);
	free_double_ptr(split_tmp);
	return (SUCCESS);
}

static double	convert_range(int a)
{
	if (a > 255)
		return (1.0);
	else
		return ((double)a / 255.0);
}

int get_ref_from_split(char *str, t_reflect *ref)
{
	char			**split_tmp;
	t_bright_color	bcolor;

	split_tmp = ft_split(str, ',');
	print_argv(split_tmp);
	if (get_size_double_ptr(split_tmp) != 3 || ft_isdigit_str(split_tmp[0], 0) == false ||
		ft_isdigit_str(split_tmp[1], 0) == false || ft_isdigit_str(split_tmp[2], 0) == false)
	{
		// printf("%s/ %s/ %s/\n", split_tmp[0],split_tmp[1],split_tmp[2]);
		// printf("%d %d %d\n", ft_isdigit_str(split_tmp[0], 0),ft_isdigit_str(split_tmp[1], 0),ft_isdigit_str(split_tmp[2], 0));
		free_double_ptr(split_tmp);
		return (ERROR);
	}
	bcolor.t = 0;
	bcolor.r = convert_range(ft_atoi(split_tmp[0]));
	bcolor.g = convert_range(ft_atoi(split_tmp[1]));
	bcolor.b = convert_range(ft_atoi(split_tmp[2]));
	ref->am = bcolor;
	ref->di = bcolor;
	ref->sp = bcolor;
	ref->sp_shininess = 2;
	ref->use_perfect_reflectance = false;
	// printf("t[%f], r[%f], g[%f], b[%f]\n", bcolor.t, bcolor.r, bcolor.g, bcolor.b);
	free_double_ptr(split_tmp);
	return (SUCCESS);
}

void	exit_error(int ret)
{
	// printf("ERROR %d\n", ret);
	exit(ret);
}

void	*get_sphere_node(char **split)
{
	t_vec3					position;
	t_reflect				ref;
	double					r;
	t_circle				*circle;
	t_obj					*obj;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (get_vec_from_split(split[1], &position) || get_ref_from_split(split[3], &ref))
		return (NULL);
	if (ft_isdouble(split[2]) == false)
		return (NULL);
	r = ft_atof(split[2]);
	circle = make_circle_instance(position, r);
	if (circle == NULL)
		return (NULL);
	obj = new_obj(O_CIRCLE, ref, circle);
	if (obj == NULL)
		return (NULL);
	return (ft_dlstnew(obj));
}

void	*get_plane_node(char **split)
{
	t_vec3					position;
	t_vec3					vertical;
	t_reflect				ref;
	t_plane					*plane;
	t_obj					*obj;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (get_vec_from_split(split[1], &position) ||
		get_vec_from_split(split[2], &vertical) ||
		get_ref_from_split(split[3], &ref))
		return (NULL);
	plane = make_plane_instance(vertical, position);
	if (plane == NULL)
		return (NULL);
	obj = new_obj(O_PLANE, ref, plane);
	if (obj == NULL)
		return (NULL);
	return (ft_dlstnew(obj));
}

void	*get_cylinder_node(char **split)
{
	t_vec3					position;
	t_vec3					axis;
	t_reflect				ref;
	t_cylinder				*cylinder;
	t_obj					*obj;
	// double					height;
	double					r;

	if (get_size_double_ptr(split) != 6)
		return (NULL);
	if (get_vec_from_split(split[1], &position) ||
		get_vec_from_split(split[2], &axis) ||
		get_ref_from_split(split[5], &ref))
		return (NULL);
	if (ft_isdouble(split[3]) == false)
		return (NULL);
	r = ft_atof(split[3]);
	// if (ft_isdouble(split[4]) == false)
	// 	return (NULL);
	// height = ft_atof(split[4]);
	cylinder = make_cylinder_instance(axis, position, r);
	if (cylinder == NULL)
		return (NULL);
	obj = new_obj(O_CYLINDER, ref, cylinder);
	if (obj == NULL)
		return (NULL);
	return (ft_dlstnew(obj));
}

void	*get_ambient_lignt(char **split)
{
	t_bright_color	*am_light;
	t_reflect		ref;
	double			raito;

	if (get_size_double_ptr(split) != 3)
		return (NULL);
	if (ft_isdouble(split[1]) == false || get_ref_from_split(split[2], &ref))
		return (NULL);
	raito = ft_atof(split[1]);
	am_light = malloc(sizeof(t_bright_color));
	if (am_light == NULL)
		return (NULL);
	*am_light = b_color_mult_constant(ref.am, raito);
	return (am_light);
}

void	*get_camera(char **split)
{
	t_ray		*ray;
	t_vec3		position;
	t_vec3		orientation;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (ft_isdigit_str(split[3], 0) == false ||
		get_vec_from_split(split[1], &position) ||
		get_vec_from_split(split[2], &orientation))
		return (NULL);
	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ray->pos = position;
	ray->distance_to_window = get_distance_to_window(ft_atoi(split[3]));
	return (ray);
}

void	*get_light_node(char **split)
{
	t_vec3			pos;
	t_reflect		ref;
	double			raito;
	t_point_light	*p_light;
	t_lightsource	*light;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (ft_isdouble(split[2]) == false ||
		get_ref_from_split(split[3], &ref) ||
		get_vec_from_split(split[1], &pos))
		return (NULL);
	raito = ft_atof(split[2]);
	p_light = make_point_light_info(pos, b_color_mult_constant(ref.am, raito));
	if (p_light == NULL)
		return (NULL);
	light = new_light(L_POINT, p_light);
	if (light == NULL)
		return (NULL);
	return (ft_dlstnew(light));
}

bool	is_valid_identifer(char *input, size_t *index)
{
	static const char	*identifers[] = {"A", "C", "L", "sp", "pl", "cy"};
	size_t	i;

	i = 0;
	while (identifers[i])
	{
		if (ft_strncmp(input, identifers[i], ft_strlen(identifers[i])) == 0)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

void	*get_identifer_info(char **split, size_t index)
{
	static void *(* const get_func[])(char **split)
		= {
		get_ambient_lignt,
		get_camera,
		get_light_node,
		get_sphere_node,
		get_plane_node,
		get_cylinder_node,
		};

	printf("size func array [%zu] divide [%zu]\n", sizeof(get_func), sizeof(get_func) / sizeof(void *));
	if (index >= sizeof(get_func) / sizeof(void *))
		return (NULL);
	else
		return (get_func[index](split));
}

int	parse_line(char *line, t_env *env)
{
	size_t				index;
	char				**split;
	void				*ret;
	bool				is_valid;

	split = ft_split(line, ' ');
	print_argv(split);
	if (split == NULL)
		return (SUCCESS);
	if (split[0] == NULL)
	{
		free (split);
		return (SUCCESS);
	}
	is_valid = is_valid_identifer(split[0], &index);
	if (is_valid)
		ret = get_identifer_info(split, index);
	free_double_ptr(split);
	if (is_valid == false || ret == NULL)
		return (ERROR);
	if (gc_add(ret) == false)
	{
		free (ret);
		return (ERROR);
	}
	if (index == 0)
		env->am_light = ret;
	else if (index == 1)
		env->eye = *(t_ray *)ret;
	else if (index < 3)
		ft_dlstadd_back(&env->light_list, ret);
	else
		ft_dlstadd_back(&env->obj_list, ret);
	return (SUCCESS);
}

int	parse_file(t_env *env, char *file)
{
	int		fd;
	char	*line;
	int		i = 0;
	(void)env;

	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		exit_error(OPEN_ERROR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		printf("line : %d\n", i);
		// if (ft_strlen(line) && parse_line(line, env) == ERROR)
		if (parse_line(line, env) == ERROR)
			exit_error(SYNTAX);
		free (line);
		i++;
	}
	if (close(fd))
		exit_error(CLOSE_ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	env;
	if (argc != 2)
		exit_error(1);
	ft_memset(&env, 0, sizeof(t_env));
	parse_file(&env, argv[1]);
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Hello world!");
	set_event(&env);
	env.img.img = mlx_new_image(env.mlx, WIN_WIDTH, WIN_HEIGHT);
	make_img6(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	printf("PUT IMAGE TO WINDOW\n");
	mlx_loop(env.mlx);

	// gc_clear();
	// printf("SUCSESS!\n");
	return (0);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q miniRT");
// }

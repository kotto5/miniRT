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
	size_t	i = 0;

	printf("===== print argv =======\n");
	if (argv == NULL)
		printf("ARG is NULL!\n");
	while (argv[i])
		printf("[%s]:", argv[i++]);
	printf(" size[%ld] \n============\n", i);
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

int get_position_from_split(char *str, t_vec3 *position)
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
	position->x = ft_atof(split_tmp[0]);
	position->y = ft_atof(split_tmp[1]);
	position->z = ft_atof(split_tmp[2]);
	printf("x[%f], y[%f], z[%f]\n", position->x, position->y, position->z);
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

int get_ref_from_split(char *str, t_bright_color *ref)
{
	char	**split_tmp;

	split_tmp = ft_split(str, ',');
	print_argv(split_tmp);
	if (get_size_double_ptr(split_tmp) != 3 || ft_isdigit_str(split_tmp[0], 0) == false ||
		ft_isdigit_str(split_tmp[1], 0) == false || ft_isdigit_str(split_tmp[2], 0) == false)
	{
		printf("%s/ %s/ %s/\n", split_tmp[0],split_tmp[1],split_tmp[2]);
		printf("%d %d %d\n", ft_isdigit_str(split_tmp[0], 0),ft_isdigit_str(split_tmp[1], 0),ft_isdigit_str(split_tmp[2], 0));
		free_double_ptr(split_tmp);
		return (ERROR);
	}
	ref->t = 0;
	ref->r = convert_range(ft_atoi(split_tmp[0]));
	ref->g = convert_range(ft_atoi(split_tmp[1]));
	ref->b = convert_range(ft_atoi(split_tmp[2]));
	printf("t[%f], r[%f], g[%f], b[%f]\n", ref->t, ref->r, ref->g, ref->b);
	free_double_ptr(split_tmp);
	return (SUCCESS);
}

void	exit_error(int ret)
{
	printf("ERROR %d\n", ret);
	exit(ret);
}

int	get_sphere(char **split, t_env *env)
{
	(void)env;
	static t_vec3			position;
	static t_bright_color	ref;
	static double			r;

	if (get_size_double_ptr(split) != 4)
		return (ERROR);
	if (get_position_from_split(split[1], &position) || get_ref_from_split(split[3], &ref))
		return (ERROR);
	if (ft_isdouble(split[2]) == false)
		return (ERROR);
	r = ft_atof(split[2]);
	// split_tmp = ft_split(split[3], ',');
	// if (get_size_double_ptr(split_tmp) != 3 || ft_isdigit_str(split_tmp[0], 0) == false ||
	// 	ft_isdigit_str(split_tmp[1], 0) == false || ft_isdigit_str(split_tmp[2], 0) == false)
	// {
	// 	free_double_ptr(split_tmp);
	// 	return (ERROR);
	// }

	return (SUCCESS);
}

int	parse_line(char *line, t_env *env)
{
	(void)env;
	char	**split;
	int		ret;

	split = ft_split(line, ' ');
	print_argv(split);
	if (split == NULL)
		return (SUCCESS);
	else if (ft_strncmp(split[0], "sp", 3) == 0)
		ret = get_sphere(split, env);
	else
		ret = ERROR;
	free_double_ptr(split);
	return (ret);
}

int	parse_file(t_env *env, char *file)
{
	int		fd;
	char	*line;
	(void)env;

	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		exit_error(OPEN_ERROR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (parse_line(line, env) == ERROR)
			exit_error(SYNTAX);
		free (line);
	}
	if (close(fd))
		exit_error(CLOSE_ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_env	env;
	(void)argv;
	if (argc != 2)
		exit_error(1);
	ft_memset(&env, 0, sizeof(t_env));
	parse_file(&env, argv[1]);
	printf("SUCSESS!\n");
	return (0);
}

__attribute__((destructor)) static void destructor()
{
	system("leaks -q miniRT");
}

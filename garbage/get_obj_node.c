

t_dlist	*get_obj_node(char **split)
{
	t_reflect				ref;
	t_obj					*obj;

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

int	parse_line(char *line, t_env *env)
{
	char				**split;
	t_dlist				*ret;
	static const char	**objs = {"sp", "pl", "cy"};
	static const char	**identifers = {"A", "C", "L", "sp", "pl", "cy"};

	is_obj = false;
	split = ft_split(line, ' ');
	print_argv(split);
	if (split == NULL)
		return (SUCCESS);
	if (split[0] == NULL)
	{
		free (split);
		return (SUCCESS);
	}
	ret = NULL;
	size_t	i = 0;
	while (objs[i])
	{
		if (ft_strncmp(split[0], objs[i], ft_strlen(objs[i])) == 0)
		{
			ret = get_obj_node(split, i);
			break;
		}
		i++;
	}
	if (ft_strncmp(split[0], "A", 3) == 0)
		ret = get_sphere_node(split);
	else if (ft_strncmp(split[0], "C", 3) == 0)
		ret = get_plane_node(split);
	if (objs[i])
	{
		free_double_ptr(split);
		if (ret == NULL)
			return (ERROR);
		ft_dlstadd_back(&env->obj_list, ret);
		return (SUCCESS);
	}
	// if (ft_strncmp(split[0], "sp", 3) == 0)
	// 	ret = get_sphere_node(split);
	// else if (ft_strncmp(split[0], "pl", 3) == 0)
	// 	ret = get_plane_node(split);
	// else if (ft_strncmp(split[0], "cy", 3) == 0)
	// 	ret = get_cylinder_node(split);

	free_double_ptr(split);
	if (ret == NULL)
		return (ERROR);
	if (gc_add(ret) == false)
	{
		free (ret);
		return (ERROR);
	}
	ft_dlstadd_back(&env->obj_list, ret);
	return (SUCCESS);
}

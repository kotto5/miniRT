/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/28 01:10:19 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static int	process_each_line(int fd, t_env *env)
{
	char	*line;
	size_t	i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (parse_line(line, env) == ERROR)
			exit_error(SYNTAX);
		free (line);
		i++;
	}
	return (0);
}

int	parse_file(t_env *env, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY, 0);
	if (fd == -1)
		exit_error(OPEN_ERROR);
	process_each_line(fd, env);
	if (close(fd))
		exit_error(ERROR);
	if (env->camera == NULL)
		exit_error(ARG_INSUFFICIENT);

	t_cone	*cone = make_cone_instance((t_vec3){0,0,10}, (t_vec3){0,1,0}, 2, (t_vec3){0,1.5,10});
	t_reflect	ref;
	get_ref_from_split("200,100,100", &ref);
	t_obj	*obj = new_obj(O_CONE, ref, cone);
	t_dlist	*node = ft_dlstnew(obj);
	gc_add(node);
	ft_dlstadd_back(&env->obj_list, node);
	return (SUCCESS);
}

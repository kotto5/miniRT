/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/05 15:57:22 by shtanemu         ###   ########.fr       */
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
	return (SUCCESS);
}

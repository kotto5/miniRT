/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:10:57 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/10 18:01:33 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//static kouzoutai ni ireru
char	*get_next_line(int fd)
{
	char		*buf;
	char		*new_line;
	size_t		allocate_size;
	static char	remain[OPEN_MAX][BUFFER_SIZE + 1UL];

	if (fd == -1)
		return (NULL);
	allocate_size = BUFFER_SIZE + 1UL;
	buf = malloc(allocate_size);
	if (!buf)
		return (NULL);
	new_line = NULL;
	if (remain[fd][0] != '\0')
	{
		allocate_size += ft_gn_strlcpy(buf, remain[fd], BUFFER_SIZE);
		ft_gn_bzero(remain[fd], BUFFER_SIZE);
		new_line = ft_gn_strchr(buf, '\n', BUFFER_SIZE);
	}
	buf = read_file(fd, buf, &new_line, &allocate_size);
	format_to_return(&buf, remain[fd], allocate_size);
	return (buf);
}

// read error to seijoukei ga same syori
char	*read_file(int fd, char *buf, char **new_line,
		size_t *allocate_size)
{
	ssize_t	read_length;
	char	*s_last;

	read_length = BUFFER_SIZE;
	while (*new_line == NULL && read_length == BUFFER_SIZE)
	{
		buf = ft_gn_realloc(buf, *allocate_size - BUFFER_SIZE, *allocate_size);
		if (!buf)
			return (NULL);
		s_last = buf + *allocate_size - BUFFER_SIZE - 1;
		ft_gn_bzero(s_last, BUFFER_SIZE + 1);
		read_length = read(fd, s_last, BUFFER_SIZE);
		*new_line = ft_gn_strchr(s_last, '\n', read_length);
		if (*allocate_size == BUFFER_SIZE + 1UL && read_length <= 0)
		{
			free (buf);
			return (NULL);
		}
		*allocate_size += read_length;
	}
	return (buf);
}

void	format_to_return(char **buf, char remain[BUFFER_SIZE], \
			size_t allocate_size)
{
	char	*new_line;

	new_line = ft_gn_strchr(*buf, '\n', allocate_size);
	if (new_line && new_line[1] != '\0')
	{
		ft_gn_strlcpy(remain, new_line + 1, BUFFER_SIZE);
		*buf = ft_gn_realloc(*buf, allocate_size, (new_line - *buf + 2));
		return ;
	}
	ft_gn_bzero(remain, BUFFER_SIZE);
}

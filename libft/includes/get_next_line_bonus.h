/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:42:06 by kakiba            #+#    #+#             */
/*   Updated: 2023/05/10 18:01:10 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

void	*ft_gn_realloc(void *ptr, size_t presize, size_t new_size);
size_t	ft_gn_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_gn_strchr(const char *s, int c, size_t length);
char	*get_next_line(int fd);
char	*read_file(int fd, char *buf, char **new_line,
			size_t *allocate_size);
void	*ft_gn_bzero(void *s, size_t n);
void	format_to_return(char **buf, char remain[BUFFER_SIZE], \
			size_t allocate_size);

#endif

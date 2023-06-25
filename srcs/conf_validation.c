/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:14:07 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 17:44:04 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include "conf_validation.h"
#include "libft.h"
#include "get_next_line_bonus.h"

int	open_valid_file(const char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (fd < 0)
	{
		put_error(strerror(errno));
		exit (EXIT_FAILURE);
	}
	return (fd);
}

char	*get_identifier(char *line)
{
	size_t	i_line;
	char	*identifer;
	char	*addrr_space;
	size_t	len_identifier;

	i_line = 0;
	while (ft_isspace(line[i_line]) == 1)
		i_line++;
	addrr_space = get_addrr_before_space(&line[i_line]);
	if (addrr_space == NULL)
		return (ft_strdup_s(line));
	len_identifier = (size_t)addrr_space - (size_t)(&line[i_line]);
	identifer = ft_strndup_s(&line[i_line], len_identifier);
	return (identifer);
}

static bool	is_valid_descriptor(const char *filepath)
{
	size_t	len_filepath;

	len_filepath = ft_strlen_s(filepath);
	if (len_filepath < 3)
	{
		put_error(ERROR_INVALID_FILE_DESCRIPTOR);
		return (false);
	}
	if (ft_strcmp_s(&filepath[len_filepath - 3], RT_DESCRIPTOR) != 0)
	{
		put_error(ERROR_INVALID_FILE_DESCRIPTOR);
		return (false);
	}
	return (true);
}

bool	is_valid(char *filepath)
{
	if (is_valid_descriptor(filepath) == false)
		return (false);
	if (has_valid_identifers(filepath) == false)
		return (false);
	if (has_essental_identifers(filepath) == false)
		return (false);
	if (has_valid_format(filepath) == false)
		return (false);
	return (true);
}

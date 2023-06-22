/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:14:07 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/22 16:40:20 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include "conf_validation.h"
#include "libft.h"
#include "get_next_line_bonus.h"

static bool	is_valid_file(const char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (fd < 0)
	{
		put_system_error();
		return (false);
	}
	close(fd);
	return (true);
}
#include <stdio.h>
static char	*get_identifier(char *line)
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
	len_identifier = (size_t)addrr_space - (size_t)&line[i_line];
	identifer = ft_strndup_s(&line[i_line], len_identifier);
	return (identifer);
}

static bool	is_valid_identifer(char *line)
{
	char		*identifer;
	size_t		i_identifiers;

	identifer = get_identifier(line);
	i_identifiers = 0;
	while (IDENTIFIERS[i_identifiers] != NULL)
	{
		if (ft_strcmp_s(identifer, IDENTIFIERS[i_identifiers]) == 0)
			break ;
		i_identifiers++;
	}
	free(identifer);
	if (IDENTIFIERS[i_identifiers] == NULL)
	{
		put_error(ERROR_INVALID_IDENTIFIER);
		return (false);
	}
	return (true);
}

static bool	has_valid_identifers(char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);
	char		*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp_s(line, "\n") != 0)
		{
			if (is_valid_identifer(line) == false)
			{
				close(fd);
				return (false);
			}
		}
	}
	close(fd);
	return (true);
}

bool	is_valid(char *filepath)
{
	if (is_valid_file(filepath) == false)
		return (false);
	if (has_valid_identifers(filepath) == false)
		return (false);
	// if (has_essental_identifers(filepath) == false)
	// 	return (false);
	// if (has_valid_format(filepath) == false)
	// 	return (false);
	return (true);
}

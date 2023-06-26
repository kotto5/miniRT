/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:36:28 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 17:42:10 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include "libft.h"
#include "conf_validation.h"

static void	set_essentials_boolean(char *line, \
									bool *has_ambient_light, \
									bool *has_camera)
{
	char	*identifer;

	identifer = get_identifier(line);
	if (ft_strcmp_s(identifer, "A") == 0)
		*has_ambient_light = true;
	if (ft_strcmp_s(identifer, "C") == 0)
		*has_camera = true;
	free(identifer);
}

bool	has_essental_identifers(const char *filepath)
{
	const int	fd = open_valid_file(filepath);
	char		*line;
	bool		has_ambient_light;
	bool		has_camera;

	has_ambient_light = false;
	has_camera = false;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp_s(line, "\n") != 0)
			set_essentials_boolean(line, &has_ambient_light, &has_camera);
		free(line);
	}
	close(fd);
	if (has_ambient_light == false || has_camera == false)
	{
		put_error(ERROR_ESSENTTIAL_IDENTIFIER);
		return (false);
	}	
	return (true);
}

static bool	is_valid_identifer(char *line)
{
	char				*identifer;
	size_t				i_identifiers;
	const static char	*identifiers[] = {\
		"A", "C", "L", "pl", "sp", "cy", NULL\
	};

	identifer = get_identifier(line);
	i_identifiers = 0;
	while (identifiers[i_identifiers] != NULL)
	{
		if (ft_strcmp_s(identifer, identifiers[i_identifiers]) == 0)
			break ;
		i_identifiers++;
	}
	free(identifer);
	if (identifiers[i_identifiers] == NULL)
	{
		put_error(ERROR_INVALID_IDENTIFIER);
		return (false);
	}
	return (true);
}

bool	has_valid_identifers(char *filepath)
{
	const int	fd = open_valid_file(filepath);
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
				free(line);
				close(fd);
				return (false);
			}
		}
		free(line);
	}
	close(fd);
	return (true);
}

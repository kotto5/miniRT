/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_valid_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:27:05 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 20:54:21 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf_validation.h"
#include "libft.h"

static bool	is_valid_ratio_in_range_al(\
	char *ratio_str, const double llim, const double ulim\
)
{
	double	ratio;

	if (ft_isdouble(ratio_str) == 0)
		return (false);
	ratio = ft_atof(ratio_str);
	return (ratio > llim && ratio <= ulim);
}

static bool	fmt_checker_ambient(const char *line)
{
	char	**contents;

	if (is_valid_n_contents(line, N_CONTENTS_AMBIENT_LIGHT) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_AMBIENT_LIGHT);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_ratio_in_range_al(contents[COL_INDEX_AMBIENT_LIGHT_RATIO], \
								LLIMIT_AMBIENT_LIGHT, ULIMIT_AMBIENT_LIGHT) \
								== false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_AMBIENT_LIGHT_RATIO);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_AMBIENT_RGB_COLOR]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	proceed_fmt_check(char *line)
{
	char				*identifier;
	size_t				i_identifiers;
	static bool			(*fmt_checker[])(const char *line) = {\
														fmt_checker_ambient, \
														fmt_checker_camera, \
														fmt_checker_light, \
														fmt_checker_plane, \
														fmt_checker_sphere, \
														fmt_checker_cylinder, \
														fmt_checker_cone};
	const static char	*identifiers[] = {\
		"A", "C", "L", "pl", "sp", "cy", "cn", NULL\
	};

	identifier = get_identifier(line);
	i_identifiers = 0;
	while (ft_strcmp_s(identifier, identifiers[i_identifiers]))
		i_identifiers++;
	if (fmt_checker[i_identifiers](line) == false)
	{
		free(identifier);
		return (false);
	}
	free(identifier);
	return (true);
}

bool	has_valid_format(const char *filepath)
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
			if (proceed_fmt_check(line) == false)
			{
				free(line);
				return (false);
			}
		}
		free(line);
	}
	return (true);
}

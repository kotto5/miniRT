/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_checker_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:18:44 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 18:18:44 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "conf_validation.h"

static bool	core_fmt_checker_light(char **contents)
{
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_LIGHT]) == false)
	{
		put_error(ERROR_INVALID_COODINATES_LIGHT);
		return (false);
	}
	if (is_valid_ratio_in_range(\
		contents[COL_INDEX_LIGHT_RATIO], LLIMIT_LIGHT, ULIMIT_LIGHT) == false)
	{
		put_error(ERROR_INVALID_LIGHT_RATIO);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_LIGHT]) == false)
	{
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	return (true);
}

bool	fmt_checker_light(const char *line)
{
	char	**contents;
	bool	is_valid;

	if (is_valid_n_contents(line, N_CONTENTS_LIGHT) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_LIGHT);
		return (false);
	}
	contents = ft_split(line, ' ');
	is_valid = core_fmt_checker_light(contents);
	free_char_matrix(contents);
	return (is_valid);
}

bool	core_fmt_spot_checker_light(char **contents)
{
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_SPOT_LIGHT]) == false)
	{
		put_error(ERROR_INVALID_COODINATES_SPOT_LIGHT);
		return (false);
	}
	if (is_valid_orientation_vector(contents[COL_INDEX_SPOT_LIGHT_OV]) == false)
	{
		put_error(ERROR_INVALID_OV_SPOT_LIGHT);
		return (false);
	}
	if (ft_isdouble(contents[COL_INDEX_SPOT_LIGHT_HEIGHT]) == 0 \
		&& ft_atof((contents[COL_INDEX_SPOT_LIGHT_HEIGHT]) > 0)
	{
		put_error(ERROR_INVALID_HEIGHT_SPOT_LIGHT);
		return (false);
	}
	if (ft_isdouble(contents[COL_INDEX_SPOT_LIGHT_DIAMETER]) == 0 \
		&& ft_atof((contents[COL_INDEX_SPOT_LIGHT_DIAMETER]) > 0)
	{
		put_error(ERROR_INVALID_DIAMETER_SPOT_LIGHT);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_SPOT_LIGHT]) == false)
	{
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	return (true);
}

bool	fmt_checker_spot_light(const char *line)
{
	char	**contents;
	bool	is_valid;

	if (is_valid_n_contents(line, N_CONTENTS_SPOT_LIGHT) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_SPOT_LIGHT);
		return (false);
	}
	contents = ft_split(line, ' ');
	is_valid = core_fmt_spot_checker_light(contents);
	free_char_matrix(contents);
	return (is_valid);
}

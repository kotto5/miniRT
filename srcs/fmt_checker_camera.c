/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_checker_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:20:12 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 18:20:12 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "conf_validation.h"

static bool	core_fmt_checker_camera(char **contents)
{
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_CAMERA]) == false)
	{
		put_error(ERROR_INVALID_COODINATES_CAMERA);
		return (false);
	}
	if (is_valid_orientation_vector(contents[COL_INDEX_OV_CAMERA]) == false)
	{
		put_error(ERROR_INVALID_OV_CAMERA);
		return (false);
	}
	if (is_valid_fov(contents[COL_INDEX_FOV_CAMERA]) == false)
	{
		put_error(ERROR_INVALID_FOV_CAMERA);
		return (false);
	}
	return (true);
}

bool	fmt_checker_camera(const char *line)
{
	char	**contents;
	bool	is_valid;

	if (is_valid_n_contents(line, N_CONTENTS_CAMERA) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_CAMERA);
		return (false);
	}
	contents = ft_split(line, ' ');
	is_valid = core_fmt_checker_camera(contents);
	free_char_matrix(contents);
	return (true);
}

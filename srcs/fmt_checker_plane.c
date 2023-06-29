/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_checker_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:49:17 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 18:49:17 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf_validation.h"
#include "libft.h"

static bool	fmt_checker_plane_main_contents(char **contents)
{
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_PLANE]) == false)
	{
		put_error(ERROR_INVALID_COODINATES_PLANE);
		return (false);
	}
	if (is_valid_orientation_vector(contents[COL_INDEX_OV_PLANE]) == false)
	{
		put_error(ERROR_INVALID_OV_PLANE);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_PLANE]) == false)
	{
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	return (true);
}

static bool	fmt_checker_plane_extra_contents(char **contents)
{
	contents[COL_INDEX_SR_PLANE] \
		= strremove_free(contents[COL_INDEX_SR_PLANE], "\n");
	contents[COL_INDEX_SR_PLANE] \
		= strremove_free(contents[COL_INDEX_SR_PLANE], "\r");
	if (is_valid_specular_reflection(contents[COL_INDEX_SR_PLANE]) == false)
	{
		put_error(ERROR_INVALID_SR);
		return (false);
	}
	return (true);
}

static bool	core_fmt_checker_plane(char **contents, const size_t n_contents)
{
	if (fmt_checker_plane_main_contents(contents) == false)
		return (false);
	if (n_contents == N_CONTENTS_PLANE_PLUS)
	{
		if (fmt_checker_plane_extra_contents(contents) == false)
			return (false);
	}
	return (true);
}

bool	fmt_checker_plane(const char *line)
{
	char	**contents;
	size_t	n_contents;
	bool	is_valid;

	contents = ft_split(line, ' ');
	n_contents = count_char_matrix_rows(contents);
	if (n_contents != N_CONTENTS_PLANE && n_contents != N_CONTENTS_PLANE_PLUS)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_N_CONTENTS_PLANE);
		return (false);
	}
	is_valid = core_fmt_checker_plane(contents, n_contents);
	free_char_matrix(contents);
	return (is_valid);
}

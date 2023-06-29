/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_checker_sphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:30:38 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 18:30:38 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf_validation.h"
#include "libft.h"

static bool	fmt_checker_sphere_main_contents(char **contents)
{
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_SPHERE]) == false)
	{
		put_error(ERROR_INVALID_COODINATES_SPHERE);
		return (false);
	}
	if (ft_isdouble(contents[COL_INDEX_DIAMETER_SPHERE]) == 0)
	{
		put_error(ERROR_INVALID_DIAMETER_SPHERE);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_SPHERE]) == false)
	{
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	return (true);
}

static bool	fmt_checker_sphere_extra_contents(char **contents)
{
	contents[COL_INDEX_SR_SPHERE] \
		= strremove_free(contents[COL_INDEX_SR_SPHERE], "\n");
	contents[COL_INDEX_SR_SPHERE] \
		= strremove_free(contents[COL_INDEX_SR_SPHERE], "\r");
	if (is_valid_specular_reflection(contents[COL_INDEX_SR_SPHERE]) \
		== false)
	{
		put_error(ERROR_INVALID_SR);
		return (false);
	}
	return (true);
}

bool	fmt_checker_sphere(const char *line)
{
	char	**contents;
	size_t	n_contents;

	contents = ft_split(line, ' ');
	n_contents = count_char_matrix_rows(contents);
	if (n_contents != N_CONTENTS_SPHERE \
		&& n_contents != N_CONTENTS_SPHERE_PLUS)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_N_CONTENTS_SPHERE);
		return (false);
	}
	if (fmt_checker_sphere_main_contents(contents) == false)
	{
		free_char_matrix(contents);
		return (false);
	}
	if (n_contents == N_CONTENTS_SPHERE_PLUS \
		&& fmt_checker_sphere_extra_contents(contents) == false)
	{
		free_char_matrix(contents);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_checker_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:49:17 by shtanemu          #+#    #+#             */
/*   Updated: 2023/07/04 15:35:21 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conf_validation.h"
#include "libft.h"

static bool	fmt_checker_triangle_main_contents(char **contents)
{
	if (!is_valid_coordinates(contents[1]) || \
		!is_valid_coordinates(contents[2]) || \
		!is_valid_coordinates(contents[3]))
	{
		put_error(ERROR_INVALID_COODINATES_TRIANGLE);
		return (false);
	}
	return (true);
}

static bool	fmt_checker_triangle_extra_contents(char **contents)
{
	contents[N_CONTENTS_TRIANGLE] \
		= strremove_free(contents[N_CONTENTS_TRIANGLE], "\n");
	contents[N_CONTENTS_TRIANGLE] \
		= strremove_free(contents[N_CONTENTS_TRIANGLE], "\r");
	if (is_valid_specular_reflection(contents[N_CONTENTS_TRIANGLE]) == false)
	{
		put_error(ERROR_INVALID_SR);
		return (false);
	}
	return (true);
}

static bool	core_fmt_checker_triangle(char **contents, const size_t n_contents)
{
	if (fmt_checker_triangle_main_contents(contents) == false)
		return (false);
	if (n_contents == N_CONTENTS_TRIANGLE + SPEC_REF_INFO)
	{
		if (fmt_checker_triangle_extra_contents(contents) == false)
			return (false);
	}
	return (true);
}

bool	fmt_checker_triangle(const char *line)
{
	char	**contents;
	size_t	n_contents;
	bool	is_valid;

	contents = ft_split(line, ' ');
	n_contents = count_char_matrix_rows(contents);
	if (n_contents != N_CONTENTS_TRIANGLE && \
		n_contents != N_CONTENTS_TRIANGLE + SPEC_REF_INFO)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_N_CONTENTS_TRIANGLE);
		return (false);
	}
	is_valid = core_fmt_checker_triangle(contents, n_contents);
	free_char_matrix(contents);
	return (is_valid);
}

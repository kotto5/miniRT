/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_rgb_in_range.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:50:14 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 18:01:45 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "conf_validation.h"

static bool	core_is_is_valid_rgb_in_range(char **rgb_array)
{
	double	r_value;
	double	g_value;
	double	b_value;

	r_value = ft_atof(rgb_array[COL_RGB_INDEX_RED]);
	g_value = ft_atof(rgb_array[COL_RGB_INDEX_GREEN]);
	b_value = ft_atof(rgb_array[COL_RGB_INDEX_BLUE]);
	return ((r_value >= LLIMIT_RGB && r_value <= ULIMIT_RGB) \
			&& (g_value >= LLIMIT_RGB && g_value <= ULIMIT_RGB) \
			&& (b_value >= LLIMIT_RGB && b_value <= ULIMIT_RGB));
}

bool	is_valid_rgb_in_range(char *rgb_str)
{
	char	**rgb_array;
	size_t	i_rgb;
	bool	is_valid;

	rgb_array = ft_split(rgb_str, ',');
	if (count_char_matrix_rows(rgb_array) != 3)
	{
		free_char_matrix(rgb_array);
		return (false);
	}
	i_rgb = 0;
	while (rgb_array[i_rgb] != NULL)
	{
		rgb_array[i_rgb] = ft_strtrim_free_s1(rgb_array[i_rgb], "\n");
		if (ft_strlen_s(rgb_array[i_rgb]) == 0)
		{
			free_char_matrix(rgb_array);
			return (false);
		}
		i_rgb++;
	}
	is_valid = core_is_is_valid_rgb_in_range(rgb_array);
	free_char_matrix(rgb_array);
	return (is_valid);
}

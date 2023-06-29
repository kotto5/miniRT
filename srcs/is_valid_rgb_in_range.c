/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_rgb_in_range.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:50:14 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 20:37:08 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "conf_validation.h"

static bool	is_valid_rgb(char *one_color)
{
	const int	value = ft_atoi(one_color);

	return (value >= LLIMIT_RGB && value <= ULIMIT_RGB);
}

bool	is_valid_rgb_in_range(char *rgb_str)
{
	char	**rgb_array;
	size_t	i_rgb;

	rgb_array = ft_split(rgb_str, ',');
	if (count_char_matrix_rows(rgb_array) != 3)
	{
		free_char_matrix(rgb_array);
		return (false);
	}
	i_rgb = 0;
	while (rgb_array[i_rgb] != NULL)
	{
		rgb_array[i_rgb] = strremove_free(rgb_array[i_rgb], "\n");
		rgb_array[i_rgb] = strremove_free(rgb_array[i_rgb], "\r");
		if (ft_strlen_s(rgb_array[i_rgb]) == 0 || \
			ft_isdigit_str(rgb_array[i_rgb], 0) == false || \
			is_valid_rgb(rgb_array[i_rgb]) == false)
		{
			free_char_matrix(rgb_array);
			return (false);
		}
		i_rgb++;
	}
	free_char_matrix(rgb_array);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_contens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 17:56:09 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/29 20:40:10 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "conf_validation.h"

bool	is_valid_specular_reflection(char *specular_reflection_str)
{
	double	specular_reflection;

	if (ft_isdouble(specular_reflection_str) == 0)
		return (false);
	specular_reflection = ft_atof(specular_reflection_str);
	return (specular_reflection >= LLIMIT_SR \
			&& specular_reflection <= ULIMIT_SR);
}

bool	is_valid_ratio_in_range(\
	char *ratio_str, const double llim, const double ulim\
)
{
	double	ratio;

	if (ft_isdouble(ratio_str) == 0)
		return (false);
	ratio = ft_atof(ratio_str);
	return (ratio >= llim && ratio <= ulim);
}

bool	is_valid_n_contents(const char *line, const size_t n_contents)
{
	char	**contents;
	size_t	len_row;

	contents = ft_split(line, ' ');
	if (contents == NULL)
		return (false);
	len_row = count_char_matrix_rows(contents);
	if (len_row != n_contents)
	{
		free_char_matrix(contents);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

bool	is_valid_coordinates(const char *coordinates_str)
{
	char	**coordinates;
	size_t	i_coordinates;

	coordinates = ft_split(coordinates_str, ',');
	if (count_char_matrix_rows(coordinates) != 3)
	{
		free_char_matrix(coordinates);
		return (false);
	}
	i_coordinates = 0;
	while (coordinates[i_coordinates] != NULL)
	{
		coordinates[i_coordinates] = \
			strremove_free(coordinates[i_coordinates], "\n");
		coordinates[i_coordinates] = \
			strremove_free(coordinates[i_coordinates], "\r");
		if (ft_strlen_s(coordinates[i_coordinates]) == 0 \
			|| ft_isdouble(coordinates[i_coordinates]) == 0)
		{
			free_char_matrix(coordinates);
			return (false);
		}
		i_coordinates++;
	}
	free_char_matrix(coordinates);
	return (true);
}

bool	is_valid_fov(char *fov_str)
{
	unsigned int	fov;

	fov_str = strremove(fov_str, "\n");
	fov_str = strremove_free(fov_str, "\r");
	if (ft_isdigit_str(fov_str, 0) == 0)
	{
		free (fov_str);
		return (false);
	}
	fov = ft_atoi(fov_str);
	free (fov_str);
	if (fov < LLIMIT_FOV || fov > ULIMIT_FOV)
		return (false);
	return (true);
}

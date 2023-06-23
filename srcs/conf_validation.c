/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:14:07 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/23 22:54:49 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include "conf_validation.h"
#include "libft.h"
#include "get_next_line_bonus.h"

static int	open_valid_file(const char *filepath)
{
	const int	fd = open(filepath, O_RDONLY);

	if (fd < 0)
	{
		put_error(strerror(errno));
		exit (EXIT_FAILURE);
	}
	return (fd);
}

static char	*get_identifier(char *line)
{
	size_t	i_line;
	char	*identifer;
	char	*addrr_space;
	size_t	len_identifier;

	i_line = 0;
	while (ft_isspace(line[i_line]) == 1)
		i_line++;
	addrr_space = get_addrr_before_space(&line[i_line]);
	if (addrr_space == NULL)
		return (ft_strdup_s(line));
	len_identifier = (size_t)addrr_space - (size_t)&line[i_line];
	identifer = ft_strndup_s(&line[i_line], len_identifier);
	return (identifer);
}

static bool	is_valid_identifer(char *line)
{
	char		*identifer;
	size_t		i_identifiers;

	identifer = get_identifier(line);
	i_identifiers = 0;
	while (IDENTIFIERS[i_identifiers] != NULL)
	{
		if (ft_strcmp_s(identifer, IDENTIFIERS[i_identifiers]) == 0)
			break ;
		i_identifiers++;
	}
	free(identifer);
	if (IDENTIFIERS[i_identifiers] == NULL)
	{
		put_error(ERROR_INVALID_IDENTIFIER);
		return (false);
	}
	return (true);
}

static bool	has_valid_identifers(char *filepath)
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

static bool	has_essental_identifers(const char *filepath)
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

static bool	is_valid_ratio_in_range(char *ratio_str, const double llim, const double ulim)
{
	double	ratio;

	if (ft_isdouble(ratio_str) == 0)
		return (false);
	ratio = ft_atof(ratio_str);
	return (ratio >= llim && ratio <= ulim);
}

static bool	is_valid_rgb_in_range(char *rgb_str)
{
	double	r_value;
	double	g_value;
	double	b_value;
	char	**rgb_array;

	rgb_array = ft_split(rgb_str, ',');
	if (count_char_matrix_rows(rgb_array) != 3)
	{
		free_char_matrix(rgb_array);
		return (false);
	}
	r_value = ft_atof(rgb_array[COL_RGB_INDEX_RED]);	
	g_value = ft_atof(rgb_array[COL_RGB_INDEX_GREEN]);	
	b_value = ft_atof(rgb_array[COL_RGB_INDEX_BLUE]);	
	free_char_matrix(rgb_array);
	return ((r_value >= LLIMIT_RGB && r_value <= ULIMIT_RGB) \
			&& (g_value >= LLIMIT_RGB && g_value <= ULIMIT_RGB) \
			&& (b_value >= LLIMIT_RGB && b_value <= ULIMIT_RGB));
}

static bool	is_valid_n_contents(const char *line, const size_t n_contents)
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

static bool	fmt_checker_ambient(const char *line)
{
	char	**contents;
	
	if (is_valid_n_contents(line, N_CONTENTS_AMBIENT_LIGHT) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_AMBIENT_LIGHT);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_ratio_in_range(contents[COL_INDEX_AMBIENT_LIGHT_RATIO], LLIMIT_AMBIENT_LIGHT, ULIMIT_AMBIENT_LIGHT) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_AMBIENT_LIGHT_RATIO);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_AMBIENT_RGB_COLOR]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_AMBIENT_LIGHT_RATIO);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	is_valid_coordinates(const char *coordinates_str)
{
	char	**coordinates;

	coordinates = ft_split(coordinates_str, ',');
	if (count_char_matrix_rows(coordinates) != 3)
	{
		free_char_matrix(coordinates);
		return (false);
	}
	if (ft_isdouble(coordinates[0]) == 0 || ft_isdouble(coordinates[1]) == 0 || ft_isdouble(coordinates[2]) == 0)
	{
		free_char_matrix(coordinates);
		return (false);
	}
	free_char_matrix(coordinates);
	return (true);
}

static bool	is_valid_orientation_vector(const char *orientation_vector_str)
{
	char	**orientation_vector;
	size_t	i_orientation_vector;
	double	value;

	orientation_vector = ft_split(orientation_vector_str, ',');
	if (count_char_matrix_rows(orientation_vector) != 3)
	{
		free_char_matrix(orientation_vector);
		return (false);
	}
	i_orientation_vector = 0;
	while (orientation_vector[i_orientation_vector] != NULL)
	{
		if (ft_isdouble(orientation_vector[i_orientation_vector]) == 0)
		{
			free_char_matrix(orientation_vector);
			return (false);
		}
		value = ft_atof(orientation_vector[i_orientation_vector]);
		if (value < LLIMIT_ORIENTATION_VECTOR || value > ULIMIT_ORIENTATION_VECTOR)
		{
			free_char_matrix(orientation_vector);
			return (false);
		}
		i_orientation_vector++;
	}
	free_char_matrix(orientation_vector);
	return (true);
}

static bool	is_valid_fov(char *fov_str)
{
	unsigned int	fov;

	if (ft_isdigit_str(fov_str, 0) == 0)
		return (false);
	fov = ft_atoi(fov_str);
	if (fov < LLIMIT_FOV || fov > ULIMIT_FOV)
		return (false);
	return (true);
}

static bool	fmt_checker_camera(const char *line)
{
	char	**contents;
	
	if (is_valid_n_contents(line, N_CONTENTS_CAMERA) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_CAMERA);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_CAMERA]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_COODINATES_CAMERA);
		return (false);
	}
	if (is_valid_orientation_vector(contents[COL_INDEX_ORIENTATION_VECTOR_CAMERA]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_ORIENTATION_VECTOR_CAMERA);
		return (false);
	}
	if (is_valid_fov(contents[COL_INDEX_FOV_CAMERA]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_FOV_CAMERA);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	fmt_checker_light(const char *line)
{
	char	**contents;

	if (is_valid_n_contents(line, N_CONTENTS_LIGHT) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_LIGHT);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_LIGHT]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_COODINATES_LIGHT);
		return (false);
	}
	if (is_valid_ratio_in_range(contents[COL_INDEX_LIGHT_RATIO], LLIMIT_LIGHT, ULIMIT_LIGHT) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_LIGHT_RATIO);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_LIGHT]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	fmt_checker_sphere(const char *line)
{
	char	**contents;
	
	if (is_valid_n_contents(line, N_CONTENTS_SPHERE) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_SPHERE);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_SPHERE]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_COODINATES_SPHERE);
		return (false);
	}
	if (ft_isdouble(contents[COL_INDEX_DIAMETER_SPHERE]) == 0)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_DIAMETER_SPHERE);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_SPHERE]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	fmt_checker_plane(const char *line)
{
	char	**contents;

	if (is_valid_n_contents(line, N_CONTENTS_PLANE) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_PLANE);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_PLANE]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_COODINATES_PLANE);
		return (false);
	}
	if (is_valid_orientation_vector(contents[COL_INDEX_ORIENTATION_VECTOR_PLANE]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_ORIENTATION_VECTOR_PLANE);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_PLANE]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	fmt_checker_cylinder(const char *line)
{
	char	**contents;

	if (is_valid_n_contents(line, N_CONTENTS_CYLINDER) == false)
	{
		put_error(ERROR_INVALID_N_CONTENTS_CYLINDER);
		return (false);
	}
	contents = ft_split(line, ' ');
	if (is_valid_coordinates(contents[COL_INDEX_COORDINATES_CYLINDER]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_COODINATES_CYLINDER);
		return (false);
	}
	if (is_valid_orientation_vector(contents[COL_INDEX_ORIENTATION_VECTOR_CYLINDER]) == false)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_ORIENTATION_VECTOR_CYLINDER);
		return (false);
	}
	if (ft_isdouble(contents[COL_INDEX_DIAMETER_CYLINDER]) == 0)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_DIAMETER_CYLINDER);
		return (false);
	}
	if (ft_isdouble(contents[COL_INDEX_HEIGHT_CYLINDER]) == 0)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_HEIGHT_CYLINDER);
		return (false);
	}
	if (is_valid_rgb_in_range(contents[COL_INDEX_RGB_COLOR_CYLINDER]) == false)
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
	char		*identifier;
	size_t		i_identifiers;
	static bool	(*fmt_checker[])(const char *line) = {fmt_checker_ambient, \
														fmt_checker_camera, \
														fmt_checker_light, \
														fmt_checker_plane, \
														fmt_checker_sphere, \
														fmt_checker_cylinder};

	identifier = get_identifier(line);
	i_identifiers = 0;
	while (ft_strcmp_s(identifier, IDENTIFIERS[i_identifiers]))
		i_identifiers++;
	if (fmt_checker[i_identifiers](line) == false)
	{
		free(identifier);
		return (false);
	}
	free(identifier);
	return (true);
}

static bool	has_valid_format(const char *filepath)
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

bool	is_valid(char *filepath)
{
	if (has_valid_identifers(filepath) == false)
		return (false);
	if (has_essental_identifers(filepath) == false)
		return (false);
	if (has_valid_format(filepath) == false)
		return (false);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:14:07 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 17:20:15 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include "conf_validation.h"
#include "libft.h"
#include "get_next_line_bonus.h"

static bool	is_valid_specular_reflection(char *specular_reflection_str)
{
	double	specular_reflection;

	if (ft_isdouble(specular_reflection_str) == 0)
		return (false);
	specular_reflection = ft_atof(specular_reflection_str);
	return (specular_reflection >= LLIMIT_SPECULAR_REFLECTION \
			&& specular_reflection <= ULIMIT_SPECULAR_REFLECTION);
}

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
	char				*identifer;
	size_t				i_identifiers;
	const static char	*identifiers[] = {"A", "C", "L", "pl", "sp", "cy", NULL};

	identifer = get_identifier(line);
	i_identifiers = 0;
	while (identifiers[i_identifiers] != NULL)
	{
		if (ft_strcmp_s(identifer, identifiers[i_identifiers]) == 0)
			break ;
		i_identifiers++;
	}
	free(identifer);
	if (identifiers[i_identifiers] == NULL)
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
		rgb_array[i_rgb] = ft_strtrim_free_s1(rgb_array[i_rgb], "\n");
		if (ft_strlen_s(rgb_array[i_rgb]) == 0)
		{
			free_char_matrix(rgb_array);
			return (false);
		}
		i_rgb++;
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
		put_error(ERROR_INVALID_RGB_COLOR_VALUE);
		return (false);
	}
	free_char_matrix(contents);
	return (true);
}

static bool	is_valid_coordinates(const char *coordinates_str)
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
		coordinates[i_coordinates] = ft_strtrim_free_s1(coordinates[i_coordinates], "\n");
		if (ft_strlen_s(coordinates[i_coordinates]) == 0)
		{
			free_char_matrix(coordinates);
			return (false);
		}
		if (ft_isdouble(coordinates[i_coordinates]) == 0)
		{
			free_char_matrix(coordinates);
			return (false);
		}
		i_coordinates++;
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
		orientation_vector[i_orientation_vector] = ft_strtrim_free_s1(orientation_vector[i_orientation_vector], "\n");
		if (ft_strlen_s(orientation_vector[i_orientation_vector]) == 0)
		{
			free_char_matrix(orientation_vector);
			return (false);
		}
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
	size_t	n_contents;
	
	contents = ft_split(line, ' ');
	n_contents = count_char_matrix_rows(contents);
	if (n_contents != N_CONTENTS_SPHERE && n_contents != N_CONTENTS_SPHERE_PLUS)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_N_CONTENTS_SPHERE);
		return (false);
	}
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
	if (n_contents == N_CONTENTS_SPHERE_PLUS)
	{
		contents[COL_INDEX_SPECULAR_REFLECTION_SPHERE] = ft_strtrim_free_s1(contents[COL_INDEX_SPECULAR_REFLECTION_SPHERE], "\n");
		if (is_valid_specular_reflection(contents[COL_INDEX_SPECULAR_REFLECTION_SPHERE]) == false)
		{
			free_char_matrix(contents);
			put_error(ERROR_INVALID_SPECULAR_REFLECTION);
			return (false);
		}
	}
	free_char_matrix(contents);
	return (true);
}

static bool	fmt_checker_plane(const char *line)
{
	char	**contents;
	size_t	n_contents;

	contents = ft_split(line, ' ');
	n_contents = count_char_matrix_rows(contents);
	if (n_contents != N_CONTENTS_PLANE && n_contents != N_CONTENTS_PLANE_PLUS)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_N_CONTENTS_PLANE);
		return (false);
	}
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
	if (n_contents == N_CONTENTS_PLANE_PLUS)
	{
		contents[COL_INDEX_SPECULAR_REFLECTION_PLANE] = ft_strtrim_free_s1(contents[COL_INDEX_SPECULAR_REFLECTION_PLANE], "\n");
		if (is_valid_specular_reflection(contents[COL_INDEX_SPECULAR_REFLECTION_PLANE]) == false)
		{
			free_char_matrix(contents);
			put_error(ERROR_INVALID_SPECULAR_REFLECTION);
			return (false);
		}
	}
	free_char_matrix(contents);
	return (true);
}

static bool	fmt_checker_cylinder(const char *line)
{
	char	**contents;
	size_t	n_contents;

	contents = ft_split(line, ' ');
	n_contents = count_char_matrix_rows(contents);
	if (n_contents != N_CONTENTS_CYLINDER && n_contents != N_CONTENTS_CYLINDER_PLUS)
	{
		free_char_matrix(contents);
		put_error(ERROR_INVALID_N_CONTENTS_CYLINDER);
		return (false);
	}
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
	if (n_contents == N_CONTENTS_CYLINDER_PLUS)
	{
		contents[COL_INDEX_SPECULAR_REFLECTION_CYLINDER] = ft_strtrim_free_s1(contents[COL_INDEX_SPECULAR_REFLECTION_CYLINDER], "\n");
		if (is_valid_specular_reflection(contents[COL_INDEX_SPECULAR_REFLECTION_CYLINDER]) == false)
		{
			free_char_matrix(contents);
			put_error(ERROR_INVALID_SPECULAR_REFLECTION);
			return (false);
		}
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
														fmt_checker_cylinder};
	const static char	*identifiers[] = {"A", "C", "L", "pl", "sp", "cy", NULL};

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

static bool	is_valid_descriptor(const char *filepath)
{
	size_t	len_filepath;

	len_filepath = ft_strlen_s(filepath);
	if (len_filepath < 3)
	{
		put_error(ERROR_INVALID_FILE_DESCRIPTOR);
		return (false);
	}
	if (ft_strcmp_s(&filepath[len_filepath - 3], RT_DESCRIPTOR) != 0)
	{
		put_error(ERROR_INVALID_FILE_DESCRIPTOR);
		return (false);
	}
	return (true);
}

bool	is_valid(char *filepath)
{
	if (is_valid_descriptor(filepath) == false)
		return (false);
	if (has_valid_identifers(filepath) == false)
		return (false);
	if (has_essental_identifers(filepath) == false)
		return (false);
	if (has_valid_format(filepath) == false)
		return (false);
	return (true);
}

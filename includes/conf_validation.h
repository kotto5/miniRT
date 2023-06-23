/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:41:45 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/23 19:48:05 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_VALIDATION_H
# define CONF_VALIDATION_H

# define IDENTIFIERS ((char const*[]){"A", "C", "L", "pl", "sp", "cy", NULL})
# define ERROR_MESSAGE_FORMAT "[Error]: miniRT: "
# define COLOR_STR_RED_FRONT "\x1b[31m"
# define COLOR_STR_RED_BACK "\x1b[0m"

# define ERROR_ESSENTTIAL_IDENTIFIER "Identifiers A and C are essential."
# define ERROR_INVALID_IDENTIFIER "A given identifier is invalid."
# define ERROR_INVALID_AMBIENT_LIGHT_RATIO "A given ambient lighting's ratio is invalid."
# define ERROR_INVALID_N_CONTENTS_AMBIENT_LIGHT "A given ambient lighting's configuration does'nt have enough contents."
# define ERROR_INVALID_RGB_COLOR_VALUE "A given rgb value of ambient lighting is invalid."

# define COL_INDEX_AMBIENT_LIGHT_RATIO 1
# define COL_INDEX_AMBIENT_RGB_COLOR 2
# define COL_RGB_INDEX_RED 0
# define COL_RGB_INDEX_GREEN 1
# define COL_RGB_INDEX_BLUE 2
# define LLIMIT_AMBIENT_LIGHT 0.0
# define ULIMIT_AMBIENT_LIGHT 1.0
# define N_CONTENTS_AMBIENT_LIGHT 3

# define ERROR_INVALID_N_CONTENTS_CAMERA "A given camera's configuration does'nt have enough contents."
# define ERROR_INVALID_COODINATES_CAMERA "A given camera's coordinates is invalid."
# define ERROR_INVALID_ORIENTATION_VECTOR_CAMERA "A given camera's orientaion vector is invalid."
# define ERROR_INVALID_FOV_CAMERA "A given camera's fov is invalid."

# define COL_INDEX_COORDINATES_CAMERA 1
# define COL_INDEX_ORIENTATION_VECTOR_CAMERA 2
# define COL_INDEX_FOV_CAMERA 3
# define N_CONTENTS_CAMERA 4

# define LLIMIT_RGB 0
# define ULIMIT_RGB 255
# define LLIMIT_ORIENTATION_VECTOR -1
# define ULIMIT_ORIENTATION_VECTOR 1
# define LLIMIT_FOV 0
# define ULIMIT_FOV 180

#include <stdbool.h>

bool	is_valid(char *filepath);
void	put_error(const char *message);

#endif
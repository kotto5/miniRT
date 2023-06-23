/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:41:45 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/23 14:26:51 by shtanemu         ###   ########.fr       */
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
# define ERROR_INVALID_AMBIENT_LIGHT_RATIO "A given ambient lighting ratio is invalid."
# define ERROR_INVALID_N_CONTENTS_AMBIENT_LIGHT "A given ambient lighting configuration does'nt have enough contents."
# define COL_INDEX_AMBIENT_LIGHT_RATIO 1


# define LLIMIT_RGB 0
# define ULIMIT_RGB 255

# define LLIMIT_AMBIENT_LIGHT 0.0
# define ULIMIT_AMBIENT_LIGHT 1.0
# define N_CONTENTS_AMBIENT_LIGHT 3

#include <stdbool.h>

bool	is_valid(char *filepath);
void	put_error(const char *message);

#endif
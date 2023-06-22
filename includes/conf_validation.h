/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conf_validation.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:41:45 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/22 23:01:40 by shtanemu         ###   ########.fr       */
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

#include <stdbool.h>

bool	is_valid(char *filepath);
void	put_error(const char *message);

#endif
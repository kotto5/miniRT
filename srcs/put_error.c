/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:29:39 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/22 22:09:07 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "conf_validation.h"

void	put_error(const char *message)
{
	write(2, COLOR_STR_RED_FRONT, sizeof(COLOR_STR_RED_FRONT));
	printf("%s%s\n", ERROR_MESSAGE_FORMAT, message);
	write(2, COLOR_STR_RED_BACK, sizeof(COLOR_STR_RED_BACK));
}

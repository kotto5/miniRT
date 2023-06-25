/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_matrix_rows.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:00:13 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 19:06:15 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<stdlib.h>

size_t	count_char_matrix_rows(char **matrix)
{
	size_t	i_row;

	if (matrix == NULL)
		return (0);
	i_row = 0;
	while (matrix[i_row] != NULL)
		i_row++;
	return (i_row);
}

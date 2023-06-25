/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:12:42 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/25 19:06:23 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_char_matrix(char **matrix)
{
	size_t	i_row;

	i_row = 0;
	while (matrix[i_row] != NULL)
	{
		free(matrix[i_row]);
		i_row++;
	}
	free(matrix);
}

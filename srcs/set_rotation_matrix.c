/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rotation_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:19:37 by shtanemu          #+#    #+#             */
/*   Updated: 2023/05/20 08:58:59 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <stdlib.h>
#include <math.h>

int	set_rxmat(double rmat[4][4], const double d)
{
	size_t	i_raw;
	size_t	i_col;

	i_raw = 0;
	while (i_raw < 4)
	{
		i_col = 0;
		while (i_col < 4)
		{
			rmat[i_raw][i_col] = 0;
			i_col++;
		}
		i_raw++;
	}
	rmat[0][0] = 1.0f;
	rmat[1][1] = cos(d);
	rmat[1][2] = -1.0f * sin(d);
	rmat[2][1] = sin(d);
	rmat[2][2] = cos(d);
	rmat[3][3] = 1.0f;
	return (0);
}

int	set_rymat(double rmat[4][4], const double d)
{
	size_t	i_raw;
	size_t	i_col;

	i_raw = 0;
	while (i_raw < 4)
	{
		i_col = 0;
		while (i_col < 4)
		{
			rmat[i_raw][i_col] = 0;
			i_col++;
		}
		i_raw++;
	}
	rmat[0][0] = cos(d);
	rmat[0][2] = sin(d);
	rmat[1][1] = 1.0f;
	rmat[2][0] = -1.0f * sin(d);
	rmat[2][2] = cos(d);
	rmat[3][3] = 1.0f;
	return (0);
}

int	set_rzmat(double rmat[4][4], const double d)
{
	size_t	i_raw;
	size_t	i_col;

	i_raw = 0;
	while (i_raw < 4)
	{
		i_col = 0;
		while (i_col < 4)
		{
			rmat[i_raw][i_col] = 0;
			i_col++;
		}
		i_raw++;
	}
	rmat[0][0] = cos(d);
	rmat[0][1] = -1.0f * sin(d);
	rmat[1][0] = sin(d);
	rmat[1][1] = cos(d);
	rmat[2][2] = 1.0f;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affine_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:27:42 by shtanemu          #+#    #+#             */
/*   Updated: 2023/05/19 15:01:20 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "all.h"

static int	set_multipled_vec_rmat(t_vec3 *v, const double rmat[4][4])
{
	double	nx;
	double	ny;
	double	nz;

	nx = v->x * rmat[0][0] + v->y * rmat[0][1] + v->z * rmat[0][2];
	ny = v->x * rmat[1][0] + v->y * rmat[1][1] + v->z * rmat[1][2];
	nz = v->x * rmat[2][0] + v->y * rmat[2][1] + v->z * rmat[2][2];
	v->x = nx;
	v->y = ny;
	v->z = nz;
	return (0);
}

static int	set_vec_rotated(t_vec3 *vec, const t_vec3 dvec)
{
	double	rmat[4][4];

	set_rxmat(rmat, dvec.x);
	set_multipled_vec_rmat(vec, rmat);
	set_rymat(rmat, dvec.y);
	set_multipled_vec_rmat(vec, rmat);
	set_rzmat(rmat, dvec.z);
	set_multipled_vec_rmat(vec, rmat);
	return (0);
}

static t_vec3	convert_input_to_dvec(const t_vec3 input)
{
	static const double	pi = 3.14159265358979323846;
	t_vec3				dvec;

	dvec.x = input.x * pi;
	dvec.y = input.y * pi;
	dvec.z = input.z * pi;
	return (dvec);
}

int	main_affine_rotation(t_vec3 *vec, const t_vec3 input)
{
	t_vec3	dvec;

	dvec = convert_input_to_dvec(input);
	set_vec_rotated(vec, dvec);
	return (0);
}
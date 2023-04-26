/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:21:01 by shtanemu          #+#    #+#             */
/*   Updated: 2023/04/26 21:55:25 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

// vec3 = vec1 + vec2
t_vec3	vec_add(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.x + vb.x;
	ans.y = va.y + vb.y;
	ans.z = va.z + vb.z;
	return (ans);
}

// vec3 = vec1 - vec2
t_vec3	vec_sub(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.x - vb.x;
	ans.y = va.y - vb.y;
	ans.z = va.z - vb.z;
	return (ans);
}

// vec3 = k * vec1
t_vec3	vec_mult(t_vec3 va, double k)
{
	t_vec3	ans;

	ans.x = va.x * k;
	ans.y = va.y * k;
	ans.z = va.z * k;
	return (ans);
}

// vec3 = vec1 ・ vec2
double	vec_dot(t_vec3 va, t_vec3 vb)
{
	return ((va.x * vb.x) + (va.y * vb.y) + (va.z * vb.z));
}

// vec3 = vec1 × vec2
t_vec3	vec_cross(t_vec3 va, t_vec3 vb)
{
	t_vec3	ans;

	ans.x = va.y * vb.z - va.z * vb.y;
	ans.y = va.z * vb.x - va.x * vb.z;
	ans.z = va.x * vb.y - va.y * vb.x;
	return (ans);
}

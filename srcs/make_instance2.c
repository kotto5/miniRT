/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_instance2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:53:36 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/04 14:53:42 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_triangle	*make_triangle_instance(t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
	t_triangle	*instance;

	instance = gc_malloc(sizeof(t_triangle));
	if (instance == NULL)
		return (NULL);
	instance->p1 = p1;
	instance->p2 = p2;
	instance->p3 = p3;
	instance->normal = vec_normalize(vec_cross(\
		vec_sub(p2, p1), vec_sub(p3, p1)));
	return (instance);
}

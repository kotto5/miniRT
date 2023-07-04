/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:52:41 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/04 14:52:46 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	*get_camera(char **split)
{
	t_camera	*camera;
	t_vec3		position;
	t_vec3		orientation;

	if (get_size_double_ptr(split) != 4)
		return (NULL);
	if (ft_isdigit_str(split[3], 0) == false || \
		set_vec_from_split(split[1], &position) || \
		set_vec_from_split(split[2], &orientation))
		return (NULL);
	camera = make_camera(ft_atof(split[3]), position, orientation);
	return (camera);
}

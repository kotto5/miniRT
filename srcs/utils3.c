/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:59:34 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/30 11:59:55 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

void	give_perfect_reflection(t_obj *obj, char *reflectance)
{
	const double	ratio = ft_atof(reflectance);

	obj->ref.use_perfect_reflectance = true;
	obj->ref.perfect_reflectance.t = ratio;
	obj->ref.perfect_reflectance.r = ratio;
	obj->ref.perfect_reflectance.g = ratio;
	obj->ref.perfect_reflectance.b = ratio;
}

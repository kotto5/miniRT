/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_triangle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:50:59 by kakiba            #+#    #+#             */
/*   Updated: 2023/07/04 14:47:34 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

double  sign(t_vec3 p1, t_vec3 p2, t_vec3 p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (t_vec3 pt, t_vec3 v1, t_vec3 v2, t_vec3 v3)
{
    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

t_intersection  get_intersection_plane_tr(const t_ray ray, t_triangle *triangle)
{
    t_obj           obj;
    t_plane         plane;

    plane.vertical = triangle->normal;
    plane.position = triangle->p1;
    obj.instance = &plane;
    return (get_intersection_plane(ray, &obj));
}

t_intersection 	get_intersection_triangle(const t_ray ray, const t_obj *obj)
{
    t_intersection  intersection;
    t_triangle      *triangle;
    t_vec3          normal;

    triangle = (t_triangle *)obj->instance;
    normal = triangle->normal;
    intersection = get_intersection_plane_tr(ray, triangle);
    if (intersection.does_intersect == false)
        return (intersection);
    // if (is_in_triangle(intersection.position, triangle) == false)
    if (PointInTriangle(intersection.position, triangle->p1, triangle->p2, triangle->p3) == false)
        intersection.does_intersect = false;
    return (intersection);
}

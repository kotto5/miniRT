/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ref.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kakiba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:27:01 by shtanemu          #+#    #+#             */
/*   Updated: 2023/06/28 21:29:31 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// deffuse refrection ... 乱反射。光がランダムな方向に分散して反射する
// 入射ベクトル incident は、計算の都合上、入射する方向の逆を取る。
// 光源をp 交点をa とすると、 p - a が入射ベクトル。

// 0 <= cos <= 1
// intensity ..? この流れだと 0 <= intensity <= 1
// 0 <= di <= 1 だし、 di = 1 - am - sp;
// return の因数が、全て 0 <= x <= 1 なら、 di = 1 - am - sp;
// だから、和が1 を超えることはない。

static t_bright_color	get_deffsuse_ref6(t_intersection intersection, \
											t_reflect ref, \
											t_lighting lighting)
{
	double	cos_incident_and_vertical;

	cos_incident_and_vertical = vec_dot(intersection.vertical_dir, \
										lighting.incident_to_light);
	if (cos_incident_and_vertical < 0)
		return (b_color_get(0, 0, 0, 0));
	return (b_color_mult_constant(b_color_mult(ref.di, \
									lighting.intensity), \
									cos_incident_and_vertical));
}

// 鏡面反射光の放射強度Rs
// Rs = Ks * Ii * cos^αθ
// 	  = Ks * Ii * (VecV ・　VecR)^α

// Ks: 鏡面反射係数（obj 依存）
// Ii: 入射光の強度 (light 依存)
// VecV は視野ベクトルの逆ベクトル	(ray と point)		方向ベクトル(正規化)
// VecR は入射光の正反射ベクトル	(light と point)	方向ベクトル(正規化)
// θ はVecV と VecR のなす角 (どうやって計算するんや？)
// α は光沢度（obj 依存） 1 <= α
// |VecV| = |VecR| = 1 (VecV と VecR は正規化する) Rs についてのでは、
//あくまで方向ベクトル

// 二つの位置ベクトルにおいて、一点から一点に対するベクトルを取得する方法
// BA = OA - OB
// 感覚 向けたい方向(BA なら A) の位置ベクトル(OA) に対して、
// 始点にしたいベクトル(OB)を指定する。

static t_bright_color	get_specular_ref6(t_lighting lighting, \
											t_intersection intersection, \
											t_ray eye, t_reflect ref_info)
{
	double	inner_product;

	inner_product = vec_dot(vec_mult(eye.dir, -1), \
									vec_sub(vec_mult(\
									intersection.vertical_dir, \
									2.0 * vec_dot(\
									intersection.vertical_dir, \
									lighting.incident_to_light)), \
									lighting.incident_to_light));
	if (fabs(vec_dot(intersection.vertical_dir, \
						lighting.incident_to_light)) < 0.01)
		return (b_color_get(0, 0, 0, 0));
	if (vec_dot(intersection.vertical_dir, lighting.incident_to_light) < 0)
		return (b_color_get(0, 0, 0, 0));
	if (inner_product < 0)
		inner_product = 0;
	if (inner_product > 1)
		inner_product = 1;
	return (b_color_mult_constant(b_color_mult(ref_info.sp, \
												lighting.intensity), \
												pow(inner_product, \
													ref_info.sp_shininess)));
}

// 半直線との交差判定の方法は　対象の形状ごとに異なる。
// しかし、どの方法であっても、交差判定に結果として交点の位置や交点における法線方向がわかれば
// 陰影の計算が可能である。
t_bright_color	get_ref6(t_intersection_info *info, \
							t_lightsource *light, \
							t_ray eye, t_scene *scene)
{
	t_bright_color		ref;
	t_lighting			lighting;

	(void)scene;
	(void)eye;
	lighting = light->lighting_at(info->intersection.position, light);
	ft_memset(&ref, 0, sizeof(t_bright_color));
	ref = b_color_add(ref, \
						get_deffsuse_ref6(info->intersection, \
											info->obj->ref, lighting));
	ref = b_color_add(ref, \
				get_specular_ref6(lighting, \
									info->intersection, \
									eye, \
									info->obj->ref));
	return (ref);
}

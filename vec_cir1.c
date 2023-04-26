/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_cir1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kakiba <kotto555555@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:50:36 by kakiba            #+#    #+#             */
/*   Updated: 2023/04/26 14:19:05 by kakiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

// A = |VecRayDir|^2
// B = 2 * (VecRayDir . (VecRayP - VecCirP))
// C = (VecRayP - VecCirP)^2 - r^2
// 交差している座標 p = VecRayP + t*VecRayDir

// double	get_ray_t_to_cir(t_ray ray, t_circle cir)
// {
// 	double	A = vec_mag_sq(ray.dir);
// 	double	B = 2.0 * vec_dot(ray.dir, (vec_sub(ray.pos, cir.pos)));
// 	double	C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
// 	double	root = B * B - (4.0 * A * C);

// 	if (root < 0)
// 		return (-1);
// 	else
// 	{
// 		root = sqrt(root);
// 		double	t1 = (-B + root) / (2.0 * A);
// 		double	t2 = (-B - root) / (2.0 * A);
// 		// printf("t1:%f, t2:%f\n", t1, t2);
// 		if ((t1 >= 0 && (t1 <= t2) )|| t2 < 0)
// 			return (t1);
// 		else if (t2 >= 0)
// 			return (t2);
// 		return (-1);
// 	}
// }

// double	get_ray_t_to_cir(t_ray ray, t_circle cir)
// {
// 	double	A = vec_mag_sq(ray.dir);
// 	double	B = 2 * vec_dot(ray.dir, vec_sub(ray.pos, cir.pos));
// 	double	C = vec_mag_sq(vec_sub(ray.pos, cir.pos)) - (cir.r * cir.r);
// 	double	root = B * B - (4.0 * A * C);
// 	if (root < 0)
// 		return (-1);
// 	else
// 		root = sqrt(root);
// 	double	t1 = (-1.0 * B) + (root / 2.0 / A);
// 	double	t2 = (-1.0 * B) - (root / 2.0 / A);
// 	if ((t1 >= 0 && (t1 <= t2) )|| t2 < 0)
// 		return (t1);
// 	else if (t2 >= 0)
// 		return (t2);
// 	return (-1);
// }

t_vec3	get_ray_intersect_vec(t_ray ray, double t)
{
	return (vec_add(vec_mult(ray.dir, t), ray.pos));
	// return (vec_sub(vec_mult(ray.dir, t), ray.pos));
	// return (vec_add(ray.pos, vec_mult(ray.dir, t)));
}

// レイのpoint に対する入射ベクトル
t_vec3	get_ray_intersect_vec_dir(t_ray ray, t_vec3 point)
{
	t_vec3	intersect_vec;

	intersect_vec = vec_sub(ray.pos, point);
	return (vec_normilize(intersect_vec));
}

// 球の法線ベクトルは、原点Cから球表面上の点Pのベクトル
// それを正規化したベクトルを返す。
t_vec3	get_cir_vertical_dir(t_circle cir, t_vec3 surface_p)
{
	t_vec3	vertical_vec = vec_sub(surface_p, cir.pos);
	return (vec_normilize(vertical_vec));
}

/*
ベクトルの正規化は、ベクトルの大きさ（長さ）を1にする処理です。
正規化されたベクトルは、方向のみを表現し、大きさの情報を持っていません。
正規化が必要かどうかは、ベクトルを使用する目的や計算の文脈によって異なります。

平面の法線ベクトルの場合、外積を計算すると、その結果のベクトルは自動的に平面に垂直になります。
しかし、その大きさは元のベクトルに依存します。
この法線ベクトルの大きさが重要でない場合（例えば、単に方向を示すだけであれば）、正規化する必要はありません。

一方、球や円柱の法線ベクトルの場合、大きさが1であることが重要です。
なぜなら、これらの法線ベクトルは光の反射や物体の接触面などの計算で使用されることが多く、大きさが1であることが前提とされているためです。
このような状況では、正規化が必要になります。

正規化が必要かどうかを判断する際には、以下の点を考慮してください:

1 ベクトルが方向のみを表現することが求められているか。
2 ベクトルの大きさが計算結果に影響を与えるか。

これらの要素を考慮して、正規化が必要かどうかを判断してください。
正規化が必要な場合は、ベクトルをその大きさで割って正規化ベクトルを得ます。
*/
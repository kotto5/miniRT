#include "all.h"

double	get_ambient_ref(double ref_am, double intensity);
double	get_specular_ref(t_point_light light, t_circle cir, t_vec3 point, t_ray eye);

t_vec3	get_light_incident_dir(t_point_light light, t_vec3 p)
{
	t_vec3	l_prime;

	l_prime = vec_sub(light.pos, p);
	return (vec_mult(l_prime, 1.0 / vec_mag(l_prime)));
}

t_vec3	get_incident_parallel_light(t_parallel_light light)
{
	t_vec3	l_prime;

	l_prime = vec_mult(light.dir, -1);
	return (vec_mult(l_prime, 1.0 / vec_mag(l_prime)));
}

double	get_ref(t_point_light light, t_circle cir, t_ray eye, double t)
{
	double	ref;
	t_vec3	intersection;

	intersection = get_ray_intersect_vec(eye, t);
	ref = 0.0;
	ref += get_ambient_ref(cir.ref.am, light.power);
	ref += get_deffsuse_ref(light, cir, intersection);
	ref += get_specular_ref(light, cir, intersection, eye);
	return (ref);
}

double	get_ambient_ref(double ref_am, double intensity)
{
	return (ref_am * intensity);
}

// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di)
double	get_deffsuse_ref(t_point_light light, t_circle cir, t_vec3 point)
{
	double	cos;

	t_vec3	n;
	t_vec3	l;

	n = get_cir_vertical_dir(cir, point);
	l = get_light_incident_dir(light, point);
	cos = vec_dot(n, l);
	if (cos < 0)
		return (0);
	return (cir.ref.di * light.power * cos);
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
// |VecV| = |VecR| = 1 (VecV と VecR は正規化する) Rs についてのでは、あくまで方向ベクトル
// 

// 二つの位置ベクトルにおいて、一点から一点に対するベクトルを取得する方法
// BA = OA - OB
// 感覚 向けたい方向(BA なら A) の位置ベクトル(OA) に対して、始点にしたいベクトル(OB)を指定する。


double	get_specular_ref(t_point_light light, t_circle cir, t_vec3 intersection, t_ray eye)
{

	double	ref = 0;
	double	Ks = cir.ref.sp;
	double	Ii = light.power;
	double	alpha = cir.ref.sp_shininess;

	t_vec3	vecV = vec_mult(eye.dir, -1);
	vecV = vec_normilize(vecV);

// vecR 1
	// t_vec3	vecR = vec_sub(light.pos, intersection);
	// vecR = vec_normilize(vecR);

// vecR 2
	t_vec3	vecN = get_cir_vertical_dir(cir, intersection);
	t_vec3	vecL = get_light_incident_dir(light, intersection);
	t_vec3	vecR = vec_sub( vec_mult(vecN, 2.0 * vec_dot(vecN, vecL)), vecL);

	double	inner_product = vec_dot(vecV, vecR);
	if (inner_product < 0)
		inner_product = 0;
	if (inner_product > 1)
		inner_product = 1;
	ref = Ks * Ii * pow(inner_product, alpha);
	return (ref);
}

// 半直線との交差判定の方法は　対象の形状ごとに異なる。
// しかし、どの方法であっても、交差判定に結果として交点の位置や交点における法線方向がわかれば
// 陰影の計算が可能である。


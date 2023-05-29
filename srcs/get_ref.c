#include "all.h"

// static t_bright_color	get_ambient_ref_double6(t_reflect ref, t_lighting lighting)
// static t_bright_color	get_ambient_ref_double6(t_reflect ref, t_bright_color am_light)
// {
// 	return (b_color_mult(ref.am, am_light));
// }

// deffuse refrection ... 乱反射。光がランダムな方向に分散して反射する
// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di)
// double	get_deffsuse_ref(t_point_light light, t_sphere cir, t_vec3 point)
// 入射ベクトル incident は、計算の都合上、入射する方向の逆を取る。
// 光源をp 交点をa とすると、 p - a が入射ベクトル。

	/*
	0 <= cos <= 1
	intensity ..? この流れだと 0 <= intensity <= 1
	0 <= di <= 1 だし、 di = 1 - am - sp;
	return の因数が、全て 0 <= x <= 1 なら、 di = 1 - am - sp; だから、和が1 を超えることはない。
	*/

static t_bright_color	get_deffsuse_ref6(t_intersection intersection, t_reflect ref, t_lighting lighting)
{
	double	cos_incident_and_vertical;

	cos_incident_and_vertical = vec_dot(intersection.vertical_dir, lighting.incident_to_light);
	if (cos_incident_and_vertical < 0)
		return (b_color_get(0, 0, 0, 0));
	// return (ref.d_di * lighting.d_intensity * cos_incident_and_vertical);
	return (b_color_mult_constant(b_color_mult(ref.di, lighting.intensity), cos_incident_and_vertical));
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


// double	get_specular_ref(t_point_light light, t_sphere cir, t_vec3 intersection, t_ray eye)
static t_bright_color	get_specular_ref6(t_lighting lighting, t_intersection intersection, t_ray eye, t_reflect ref_info)
{
	// double	ref = 0;
	// double	Ks = ref_info.d_sp;
	// double	Ii = lighting.d_intensity;

	if (fabs(vec_dot(intersection.vertical_dir, lighting.incident_to_light)) < 0.01)
		return (b_color_get(0, 0, 0, 0));

	double	alpha = ref_info.sp_shininess;

	t_vec3	inverse_eyedir = vec_mult(eye.dir, -1);

	t_vec3	vertical = intersection.vertical_dir;
	// t_vec3	vecL = get_light_incident_dir(light, intersection);
	// t_vec3	incident = vec_normalize(vec_sub(light.pos, intersection.position));
	t_vec3	incident = lighting.incident_to_light;
	t_vec3	regular_ref_incident = vec_sub( vec_mult(vertical, 2.0 * vec_dot(vertical, incident)), incident);
	if (vec_dot(vertical, incident) < 0)
	{
		// printf("===============");
		return (b_color_get(0, 0, 0, 0));
	}
	double	inner_product = vec_dot(inverse_eyedir, regular_ref_incident);
	// if (inner_product > 0.000)
	// 	printf("");
	if (inner_product < 0)
		inner_product = 0;
	if (inner_product > 1)
		inner_product = 1;
	// ref = Ks * Ii * pow(inner_product, alpha);
	return (b_color_mult_constant(b_color_mult(ref_info.sp, lighting.intensity), pow(inner_product, alpha)));
}

// 半直線との交差判定の方法は　対象の形状ごとに異なる。
// しかし、どの方法であっても、交差判定に結果として交点の位置や交点における法線方向がわかれば
// 陰影の計算が可能である。
// t_bright_color	get_ref6(t_intersection intersection, t_reflect ref_info, t_lightsource *light, t_ray eye)
t_bright_color	get_ref6(t_intersection_info *info, t_lightsource *light, t_ray eye, t_scene *scene)
{
	(void)scene;
	(void)eye;
	t_bright_color		ref;
	const t_lighting	lighting = light->lighting_at(info->intersection.position, light);

	ft_memset(&ref, 0, sizeof(t_bright_color));

// うっすらと光の線が出るときにこれで対処できる 円とか円柱とか
// inside sy 3 みたいに、側面に垂直に光宛てられた時の挙動は変わっちゃう

	// printf(" [%f]  \n", vec_dot(info->intersection.vertical_dir, lighting.incident_to_light));
	// b_color_add(ref, get_deffsuse_ref6(info->intersection, info->obj->ref, lighting));
	ref = b_color_add(ref, get_deffsuse_ref6(info->intersection, info->obj->ref, lighting));

	// b_color_add(ref, get_specular_ref6(lighting, info->intersection, eye, info->obj->ref));
	ref = b_color_add(ref, get_specular_ref6(lighting, info->intersection, eye, info->obj->ref));
	if (ref.r > 1.0)
	{
		// printf("ref is over 1   ref:%f", ref.r);
		// print_vec(intersection.position, "intersection position");
		// exit(1);
	}
	return (ref);
}

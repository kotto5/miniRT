#include "all.h"

double	get_min_double(const double a, const double b)
{
	if (a > b)
		return (b);
	return (a);
}

double	get_max_double(const double a, const double b)
{
	if (a > b)
		return (a);
	return (b);
}

int	set_custom_rotated_vector(
	t_vec3 *vec, const t_vec3 center, const t_vec3 rdvec)
{
	t_vec3	nvec;

	nvec = vec_sub(*vec, center);
	main_affine_rotation(&nvec, rdvec);
	nvec = vec_add(nvec, center);
	set_vec3(vec, nvec.x, nvec.y, nvec.z);
	return (0);
}

// double angleBetween(t_vec3 v1, t_vec3 v2) {
// 	double	dot = dotProduct(v1, v2);
// 	double	mag1 = magnitude(v1);
// 	double	mag2 = magnitude(v2);

// 	return acos(dot / (mag1 * mag2));
// }

t_vec3 rotate_vec(t_vec3 v, t_vec3 k, double theta) {
	t_vec3 vRot;
	double costheta = cos(theta);
	double sintheta = sin(theta);

	vRot.x = v.x * costheta + vec_cross(k, v).x * sintheta + k.x * vec_dot(k, v) * (1 - costheta);
	vRot.y = v.y * costheta + vec_cross(k, v).y * sintheta + k.y * vec_dot(k, v) * (1 - costheta);
	vRot.z = v.z * costheta + vec_cross(k, v).z * sintheta + k.z * vec_dot(k, v) * (1 - costheta);

	return vRot;
}
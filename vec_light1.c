#include "all.h"

double	get_ambient_ref(t_reflect ref, double intensity);
double	get_specular_ref(t_point_light light, t_circle cir, t_vec3 point, t_ray eye);

t_vec3	get_incident_point_light(t_point_light light, t_vec3 p)
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
	t_vec3	point = get_intersect_point_ray_cir(eye, t);

	ref = 0.0;
	ref += get_deffsuse_ref(light, cir, point);
	ref += get_ambient_ref(cir.ref, light.power);
	// ref += get_specular_ref(light, cir, point, eye);
	return (ref);
}

// double	get_deffsuse_ref(double power, t_vec3 light_p, t_vec3 p, t_vec3 n, double di)
double	get_deffsuse_ref(t_point_light light, t_circle cir, t_vec3 point)
{
	double	cos;

	t_vec3	n;
	t_vec3	l;

	n = get_normal_cir(cir, point);
	l = get_incident_point_light(light, point);
	cos = vec_dot(n, l);

	// printf("=====================\nNormal vector: (%f, %f, %f)\n", n.x, n.y, n.z);
	// printf("Incident vector: (%f, %f, %f)\n", l.x, l.y, l.z);
	// printf("Dot product: %f\n", cos);

	if (cos < 0)
		return (0);
	return (cir.ref.di * light.power * cos);
}

double	get_ambient_ref(t_reflect ref, double intensity)
{
	return (ref.am * intensity);
}

double	get_specular_ref(t_point_light light, t_circle cir, t_vec3 point, t_ray eye)
{

	double	ref;
	t_vec3	norm_vec = get_normal_cir(cir, point);
	t_vec3	incident_vec =  vec_dot(point, light.pos);
	// double	cos_theta = vec_dot(d, n) / (vec_mag(d) * vec_mag(n));
	// double	theta = acos(cos_theta);
	// t_vec3	l = 
	t_vec3	r = vec_sub(incident_vec, vec_mult(norm_vec, vec_dot(incident_vec, norm_vec) * -2 * (1 / vec_mag_sq(norm_vec))));

	ref = cir.ref.sp * light.power * 
		pow(vec_dot(vec_mult(eye.dir, -1), r), cir.ref.sp_shininess);
	return (ref);
}

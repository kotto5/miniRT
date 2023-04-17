#include "all.h"

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

	// printf("search:%f, %f, %f\n", cir.ref.di, light.power, cos);
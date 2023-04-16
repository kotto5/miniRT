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

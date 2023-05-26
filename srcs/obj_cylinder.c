#include "all.h"

static int	set_solutions(t_ray ray, t_cylinder *cylinder, double t[2])
{
	t_vec3	P = vec_sub(ray.dir, (vec_mult(cylinder->vertical, vec_dot(ray.dir, cylinder->vertical))));
	t_vec3	Q = vec_sub(vec_sub(ray.pos, cylinder->position), vec_mult(cylinder->vertical, vec_dot(vec_sub(ray.pos, cylinder->position), cylinder->vertical)));
	double	A = vec_mag_sq(P);
	double	B = 2 * vec_dot(P, Q);
	double	root = pow(B, 2) - 4 * A * (vec_mag_sq(Q) - pow(cylinder->r, 2));
	if (root < 0)
		return (ERROR);
	t[0] = (-B + sqrt(root)) / (2 * A);
	t[1] = (-B - sqrt(root)) / (2 * A);
	return (SUCCESS);
}

// dot < 0 == 円柱の下
// vecmug > height == 円柱の上
static bool		is_on_cylinder(t_ray ray, t_cylinder *cylinder, double t)
{
	t_vec3	intersection_pos = vec_add(ray.pos, vec_mult(ray.dir, t));
	t_vec3	center_to_intersect = vec_sub(intersection_pos, cylinder->position);
	double	projection_length = vec_dot(center_to_intersect, cylinder->vertical);

	// t_vec3	intersection_pos = vec_add(ray.pos, vec_mult(ray.dir, t));
	// t_vec3	center_to_intersect = vec_sub(cylinder->position, intersection_pos);
	// double	projection_length = vec_dot(cylinder->vertical, center_to_intersect);

	// if (projection_length == 0.00)
	if (projection_length < 0.00)
		return (false);
	t_vec3	projection = vec_mult(cylinder->vertical, projection_length);
	(void)projection;
	if (vec_mag(projection) > cylinder->height)
		return (false);
	return (true);
}

static int	get_t_ray_cylinder(t_ray ray, t_cylinder *cylinder, double *solution)
{
	double	t[2];
	bool	is_on[2];

	ft_memset(is_on, 0, sizeof(is_on));
	if (set_solutions(ray, cylinder, t))
		return (-1);
	if (t[0] < 0.0 && t[1] < 0.0)
		return (ERROR);
	else
	{
		if (t[0] > 0.0)
			is_on[0] = is_on_cylinder(ray, cylinder, t[0]);
		if (t[1] > 0.0)
			is_on[1] = is_on_cylinder(ray, cylinder, t[1]);
		if ((!is_on[0] && !is_on[1]))
			return (ERROR);
		else if (!is_on[1])
			*solution = t[0];
		else if (!is_on[0])
			*solution = t[1];
		else
			*solution = get_min_double(t[0], t[1]);
	}
	return (SUCCESS);
}

t_vec3	get_cylinder_normal(t_vec3 intersect, t_vec3 vertical, t_vec3 cylinder_center)
{
	t_vec3 to_center;
	double projection_length;
	t_vec3 projection;
	t_vec3 normal;

	// Calculate the vector from the point to the center of the cylinder
	to_center = vec_sub(intersect, cylinder_center);
	// to_center = vec_sub(cylinder_center, intersect);

	// Project this vector onto the vertical vector of the cylinder
	projection_length = vec_dot(to_center, vertical);
	projection = vec_mult(vertical, projection_length);

	// Subtract the projection from the original vector to get the normal
	normal = vec_sub(to_center, projection);

	// Normalize the normal vector before returning
	return vec_normalize(normal);
}
// C    0,10,-10        0,-1,1        90


t_intersection	get_intersection_cylinder(const t_ray ray, const t_obj *obj)
{
	t_cylinder		*cylinder;
	t_intersection	intersection;
	double	t;
	t_vec3	dt;

	cylinder = obj->instance;
	intersection.does_intersect = false;
	if (get_t_ray_cylinder(ray, cylinder, &t))
		return(intersection);
	intersection.does_intersect = true;
	dt = vec_mult(ray.dir, t);
	intersection.position = vec_add(ray.pos, dt);
	intersection.distance = vec_mag(dt);
	intersection.vertical_dir = get_cylinder_normal(intersection.position, cylinder->vertical, cylinder->position);
	if (vec_dot(intersection.vertical_dir, ray.dir) >= 0.0)
	{
		intersection.vertical_dir = vec_mult(intersection.vertical_dir, -1);
		intersection.is_inside = true;
	}
	return (intersection);
}

bool	is_inside_cylinder(const t_obj *obj, const t_vec3 point)
{
(void)obj;
(void)point;
return (false);
}


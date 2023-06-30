#include "struct.h"

void	give_perfect_reflection(t_obj *obj, char *reflectance)
{
	const double	ratio = ft_atof(reflectance);

	obj->ref.use_perfect_reflectance = true;
	obj->ref.perfect_reflectance.t = ratio;
	obj->ref.perfect_reflectance.r = ratio;
	obj->ref.perfect_reflectance.g = ratio;
	obj->ref.perfect_reflectance.b = ratio;
}

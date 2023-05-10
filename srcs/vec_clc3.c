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

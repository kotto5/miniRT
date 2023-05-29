#include "all.h"

static double	get_minimum(double a, double b, double c)
{
	if (a <= b && a <= c )
		return (a);
	else if (b <= a && b <= c)
		return (b);
	else
		return (c);
}

static double	get_maximum(double a, double b, double c)
{
	if (a >= b && a >= c )
		return (a);
	else if (b >= a && b >= c)
		return (b);
	else
		return (c);
}

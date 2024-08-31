#include "objects.h"
#include "rtmath.h"

void sphere(t_sphere *sphere, t_double4 *center, double radius)
{
	sphere->center = *center;
	sphere->radius = radius;
}
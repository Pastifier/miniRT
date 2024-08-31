#include "rtmath.h"
#include "linear_algebra.h"
#include "objects.h"

void ray_position(t_double4 *result, t_ray *ray, double t)
{	
	t_double4 scaled;

	d4mul(&scaled, &ray->direction, t);
	d4add(result, &ray->origin, &scaled);
}



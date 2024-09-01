#include "rtmath.h"
#include "linear_algebra.h"
#include "objects.h"
#include "matrix.h"

void ray_create(t_ray *ray, t_double4 *origin, t_double4 *direction)
{
	t_intersections itx;
	ray->origin = *origin;
	ray->direction = *direction;
	itx.count = 0;
	ray->itx = itx;
}

void ray_position(t_double4 *result, t_ray *ray, double t)
{	
	result->x = ray->origin.x + ray->direction.x * t;
	result->y = ray->origin.y + ray->direction.y * t;
	result->z = ray->origin.z + ray->direction.z * t;
	result->w = 1.0;
}

void	ray_transform(t_ray *ray, t_mat4x4 *matrix)
{
	t_double4	origin;
	t_double4	direction;

	origin = ray->origin;
	direction = ray->direction;
	ray->origin = mat4x4_cross_vec(matrix, &origin);
	ray->direction = mat4x4_cross_vec(matrix, &direction);
}

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"

void cube(t_object *cube, t_double4 *center, double length, t_mat4x4 *transform)
{
	cube->type = OBJ_CUBE;
	if (center)
		cube->center = *center;
	else
		point(&cube->center, 0.0, 0.0, 0.0);
	if (transform)
		cube->transform = *transform;
	else
		cube->transform = mat4x4_identity();
	cube->obj.cube.side_length = length;
	cube->material = default_material();
}

static void check_axis(double origin, double direction, double side_length, double *tmin, double *tmax)
{
	double half_side = side_length / 2.0;
	double tmin_numerator = (-half_side - origin);
	double tmax_numerator = (half_side - origin);
	double temp;

	if (fabs(direction) >= EPSILON)
	{
		*tmin = tmin_numerator / direction;
		*tmax = tmax_numerator / direction;
	}
	else
	{
		*tmin = tmin_numerator * INFINITY;
		*tmax = tmax_numerator * INFINITY;
	}

	if (*tmin > *tmax)
	{
		temp = *tmin;
		*tmin = *tmax;
		*tmax = temp;
	}
}

void intersect_cube(t_ray *ray, t_object *cube, t_intersections *xs)
{
	t_mat4x4 inv_transform;
	t_ray transformed_ray;
	double xtmin, xtmax;
	double ytmin, ytmax;
	double ztmin, ztmax;
	double tmin, tmax;
	double side_length = cube->obj.cube.side_length;

	inv_transform = mat4x4_inverse(&cube->transform);
	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(inv_transform));

	check_axis(transformed_ray.origin.x, transformed_ray.direction.x, side_length, &xtmin, &xtmax);
	check_axis(transformed_ray.origin.y, transformed_ray.direction.y, side_length, &ytmin, &ytmax);
	check_axis(transformed_ray.origin.z, transformed_ray.direction.z, side_length, &ztmin, &ztmax);

	tmin = fmax(fmax(xtmin, ytmin), ztmin);
	tmax = fmin(fmin(xtmax, ytmax), ztmax);

	if (tmin > tmax)
		return; // Ray misses the cube

	// Register the intersection points
	xs->data[xs->count].object = cube;
	xs->data[xs->count++].t = tmin;
	xs->data[xs->count].object = cube;
	xs->data[xs->count++].t = tmax;
}

t_double4 cube_normal_at(t_object *cube, t_double4 *world_point)
{
	t_double4 object_point;
	t_double4 normal;
	t_mat4x4 inv_transform = mat4x4_inverse(&cube->transform);

	object_point = mat4x4_cross_vec(&inv_transform, world_point);

	double maxc = fmax(fmax(fabs(object_point.x), fabs(object_point.y)), fabs(object_point.z));

	if (maxc == fabs(object_point.x))
		vector(&normal, object_point.x, 0, 0);
	else if (maxc == fabs(object_point.y))
		vector(&normal, 0, object_point.y, 0);
	else
		vector(&normal, 0, 0, object_point.z);

	return normal;
}
#include "miniRT.h"
#include "macros.h"

bool check_cap(t_ray *ray, float t, float radius)
{
	float	x;
	float	z;

	x = ray->origin.x + t * ray->dir.x;
	z = ray->origin.z + t * ray->dir.z;
	return (x * x + z * z) <= (radius * radius);
}

void intersect_cone_caps(t_ray *ray, t_obj *cone, t_itx_grp *xs)
{
	float	t_cap;
	t_vec4s	cap_point;
	
	if (!cone->specs.closed || fabsf(ray->dir.y) < EPSILON)
		return;
	t_cap = (cone->specs.min - ray->origin.y) / ray->dir.y;
	cap_point = lag_vec4s_add_ret(ray->origin, lag_vec4s_scaleby_ret(ray->dir, t_cap));
	// Step 2: Check if intersection lies within the radius of the cap
	if ((cap_point.x * cap_point.x + cap_point.z * cap_point.z) <= powf(cone->specs.radius, 2))
	{
		// Add valid intersection to the intersection group
		xs->arr[xs->count].t = t_cap;
		xs->arr[xs->count].object = cone;
		lag_vec4sv_init(&xs->arr[xs->count].normalv, 0, 1, 0); // Normal pointing outwards
		xs->count++;
	}
}

t_vec4s	cone_normal_at(t_obj *cone, t_vec4s *world_point)
{
	t_vec4s local_point;
	t_vec4s local_normal;
	t_mat4s transposed_inv;
	t_vec4s world_normal;
	float dist;

	local_point = lag_mat4s_cross_vec4s(cone->inv_transform, *world_point);
	dist = local_point.x * local_point.x + local_point.z * local_point.z;

	if (dist < cone->specs.radius * cone->specs.radius && local_point.y >= (cone->specs.max - EPSILON))
		lag_vec4sv_init(&local_normal, 0, 1, 0); // Normal for the cap
	else
		lag_vec4sv_init(&local_normal, local_point.x, 0, local_point.z); // Side normal

	transposed_inv = lag_mat4s_transpose_ret(cone->inv_transform);
	world_normal = lag_mat4s_cross_vec4s(transposed_inv, local_normal);
	world_normal.w = 0;
	lag_vec4s_normalize(&world_normal);

	return world_normal;
}

float	co_discriminant(t_ray transformed_ray, float *t_values)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	sqrt_disc;

	a = powf(transformed_ray.dir.x, 2) - powf(transformed_ray.dir.y, 2) + powf(transformed_ray.dir.z, 2);
	b = 2 * (transformed_ray.origin.x * transformed_ray.dir.x - transformed_ray.origin.y * transformed_ray.dir.y + transformed_ray.origin.z * transformed_ray.dir.z);
	c = powf(transformed_ray.origin.x, 2) - powf(transformed_ray.origin.y, 2) + powf(transformed_ray.origin.z, 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (false);
	sqrt_disc = sqrtf(disc);
	t_values[0] = (-b - sqrt_disc) / (2 * a);
	t_values[1] = (-b + sqrt_disc) / (2 * a);
	if (t_values[0] > t_values[1])
	{
		disc = t_values[0];
		t_values[0] = t_values[1];
		t_values[1] = disc;
	}
	return (true);
}
void intersect_cone(t_ray *ray, t_obj *cone, t_itx_grp *xs)
{
	t_ray	transformed_ray;
	float	t_values[2];
	float	y_values[2];

	ray->xs.count = 0;
	ray->xs.arr->object = cone;
	transformed_ray = *ray;
	ray_transform(&transformed_ray, &cone->inv_transform);
	if (!co_discriminant(transformed_ray, t_values))
		return;
	y_values[0] = transformed_ray.origin.y + t_values[0] * transformed_ray.dir.y;
	if (y_values[0] > cone->specs.min && y_values[0] < cone->specs.max)
	{
		xs->arr[xs->count].object = cone;
		xs->arr[xs->count++].t = t_values[0];
	}
	y_values[1] = transformed_ray.origin.y + t_values[1] * transformed_ray.dir.y;
	if (y_values[1] > cone->specs.min && y_values[1] < cone->specs.max)
	{
		xs->arr[xs->count].object = cone;
		xs->arr[xs->count++].t = t_values[1];
	}
	intersect_cone_caps(&transformed_ray, cone, xs);
}
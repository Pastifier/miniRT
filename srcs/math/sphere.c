#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"
#include <stdio.h>

void sphere(t_sphere *sphere, t_double4 *center, double radius, t_mat4x4 *transform)
{
	sphere->center = *center;
	sphere->radius = radius;
	if (transform)
		sphere->transform = *transform;
	else
		sphere->transform = mat4x4_identity();
	sphere->material = default_material();
}

t_double4	sphere_normal_at(t_sphere *sphere, t_double4 *world_point)
{
	t_double4 object_n_p[2];
	t_double4 world_n;
	t_double4 origin;
	t_mat4x4 inv_transform;
	t_mat4x4 transposed_inv;

	point(&origin, 0.0, 0.0, 0.0);
	inv_transform = mat4x4_inverse(&sphere->transform);
	transposed_inv = mat4x4_transpose(&inv_transform);
	object_n_p[1] = mat4x4_cross_vec(&inv_transform, world_point);
	d4sub(&object_n_p[0], &object_n_p[1], &origin);
	world_n = mat4x4_cross_vec(&transposed_inv, &object_n_p[0]);
	world_n.w = 0;
	vnormalize(&world_n);
	return world_n;
}

static void sphere_discriminant(t_ray *ray, t_sphere *sphere, t_discriminant *disc)
{
	t_double4 sphere_to_ray;

	d4sub(&sphere_to_ray, &ray->origin, &sphere->center);
	// d4sub(&sphere_to_ray, &sphere->center, &ray->origin); // Changed to this
	disc->a = vdot(&ray->direction, &ray->direction);
	disc->b = 2.0 * vdot(&sphere_to_ray, &ray->direction);
	// disc->b = -2.0 * vdot(&sphere_to_ray, &ray->direction); // Changed to this
	disc->c = vdot(&sphere_to_ray, &sphere_to_ray) - (sphere->radius * sphere->radius);
	disc->disc = disc->b * disc->b - 4.0 * disc->a * disc->c;
	if (disc->disc < 0)
		disc->sqrt_disc = -1.0;
	else
		disc->sqrt_disc = sqrt(disc->disc);
}

static void sphere_t_values(t_discriminant *disc, double t_values[], int *t_count)
{
	*t_count = 0;
	if (disc->sqrt_disc < 0) // sqrts of negative numbers are imaginary
		return;
	t_values[0] = (-disc->b - disc->sqrt_disc) / (2.0 * disc->a);
	t_values[1] = (-disc->b + disc->sqrt_disc) / (2.0 * disc->a);
	// if (disc->sqrt_disc == 0)
	// 	*t_count = 1;
	// else
	// 	*t_count = 2;
	if (*t_count + 2 < MAX_INTERSECTIONS)
		*t_count += 2;
}

void intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_discriminant disc;
	double t_values[MAX_INTERSECTIONS];
	int t_count;
	t_mat4x4 inv_transform;

	t_count = 0;
	inv_transform = mat4x4_inverse(&sphere->transform);
	ray->itx.count = 0;
	ray_transform(ray, &(inv_transform));
	sphere_discriminant(ray, sphere, &disc);
	if (disc.disc < 0)
		return ;
	sphere_t_values(&disc, t_values, &t_count);
	ray->itx.count = t_count;
	store_intersections(&ray->itx, t_values, OBJ_SPHERE, sphere);
	quick_sort_intersections(ray->itx.data, ray->itx.count);
	// ray_position(&ray->itx.data[0].itx_p, ray, ray->itx.data[0].t);
	// if (t_count == 2)
	// 	ray_position(&ray->itx.data[1].itx_p, ray, ray->itx.data[1].t);
	// We'll see...
}

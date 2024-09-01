#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"

void sphere(t_sphere *sphere, t_double4 *center, double radius, t_mat4x4 *transform)
{
	t_color c;

	sphere->center = *center;
	sphere->radius = radius;
	if (transform)
		sphere->transform = *transform;
	else
		sphere->transform = mat4x4_identity();
	color(&c, 1.0, 0.0, 0.0);
	sphere->color = c;
}

static void sphere_discriminant(t_ray *ray, t_sphere *sphere, t_discriminant *disc)
{
	t_double4 sphere_to_ray;

	d4sub(&sphere_to_ray, &ray->origin, &sphere->center);
	disc->a = vdot(&ray->direction, &ray->direction);
	disc->b = 2.0 * vdot(&ray->direction, &sphere_to_ray);
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
	if (disc->sqrt_disc < 0)
		return;
	t_values[0] = (-disc->b - disc->sqrt_disc) / (2.0 * disc->a);
	t_values[1] = (-disc->b + disc->sqrt_disc) / (2.0 * disc->a);
	if (disc->sqrt_disc == 0)
		*t_count = 1;
	else
		*t_count = 2;
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
	sphere_t_values(&disc, t_values, &t_count);
	ray->itx.count = t_count;
	store_intersections(&ray->itx, t_values, OBJ_SPHERE, sphere);
	sort_intersections(&ray->itx);
}
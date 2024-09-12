/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:36 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/12 22:36:25 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"

void sphere(t_object *sphere, t_double4 *center, double radius, t_mat4x4 *transform)
{
	sphere->type = OBJ_SPHERE;
	if (center)
		sphere->center = *center;
	else
		point(&sphere->center, 0.0, 0.0, 0.0);
	sphere->obj.sphere.radius = radius;
	if (transform)
		sphere->transform = *transform;
	else
		sphere->transform = mat4x4_identity();
	sphere->material = default_material();
}

t_double4	sphere_normal_at(t_object *sphere, t_double4 *world_point)
{
	t_double4 object_n_p[2];
	t_double4 world_n;
	t_mat4x4 inv_transform;
	t_mat4x4 transposed_inv;
	t_double4 origin;

	origin = sphere->center;
	inv_transform = mat4x4_inverse(&sphere->transform);
	object_n_p[1] = mat4x4_cross_vec(&inv_transform, world_point);
	d4sub(&object_n_p[0], &object_n_p[1], &origin);
	transposed_inv = mat4x4_transpose(&inv_transform);
	world_n = mat4x4_cross_vec(&transposed_inv, &object_n_p[0]);
	world_n.w = 0;
	vnormalize(&world_n);
	return world_n;
}

static void sphere_discriminant(t_ray *ray, t_object *sphere, t_discriminant *disc)
{
	t_double4 sphere_to_ray;

	d4sub(&sphere_to_ray, &ray->origin, &sphere->center);
	disc->a = vdot(&ray->direction, &ray->direction);
	disc->b = 2.0 * vdot(&sphere_to_ray, &ray->direction);
	disc->c = vdot(&sphere_to_ray, &sphere_to_ray) - (sphere->obj.sphere.radius * sphere->obj.sphere.radius);
	disc->disc = disc->b * disc->b - 4.0 * disc->a * disc->c;
	if (disc->disc < 0)
		disc->sqrt_disc = -1.0;
	else
		disc->sqrt_disc = sqrt(disc->disc);
}

static void sphere_t_values(t_discriminant *disc, double t_values[], int *t_count)
{
	*t_count = 0;
	if (disc->sqrt_disc < 0) // sqrts of negative numbers are imaginary // (Psst! This check is unneeded<3)
		return;
	t_values[0] = (-disc->b - disc->sqrt_disc) / (2.0 * disc->a);
	t_values[1] = (-disc->b + disc->sqrt_disc) / (2.0 * disc->a);
	if (*t_count + 2 < MAX_INTERSECTIONS)
		*t_count += 2;
}

void intersect_sphere(t_ray *ray, t_object *sphere, t_intersections *xs)
{
	t_discriminant disc;
	double t_values[MAX_INTERSECTIONS];
	int t_count;
	t_mat4x4 inv_transform;
	t_ray transformed_ray;

	t_count = 0;
	inv_transform = mat4x4_inverse(&sphere->transform);
	ray->itx.count = 0;
	ray->itx.data->object = sphere;
	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(inv_transform));
	sphere_discriminant(&transformed_ray, sphere, &disc);
	if (disc.disc < 0)
		return ;
	sphere_t_values(&disc, t_values, &t_count);
	xs->data[xs->count].object = sphere;
	xs->data[xs->count++].t = t_values[0];
	xs->data[xs->count].object = sphere;
	xs->data[xs->count++].t = t_values[1];
}

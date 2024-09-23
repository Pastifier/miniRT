/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:57:56 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/23 12:16:53 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"
#include <stdio.h>

void cylinder(t_object *cy, t_double4 *center, double radius, t_mat4x4 *transform)
{
	cy->type = OBJ_CYLINDER;
	if (center)
		cy->center = *center;
	else
		point(&cy->center, 0.0, 0.0, 0.0);
	cy->obj.cy.radius = radius;
	if (transform)
		cy->transform = *transform;
	else
		cy->transform = mat4x4_identity();
	cy->material = default_material();
	cy->obj.cy.min = -1;
	cy->obj.cy.max = 1;
	cy->obj.cy.closed = true;
}

t_double4 cylinder_normal_at(t_object *cylinder, t_double4 *world_point)
{
	t_mat4x4 inv_transform;
	t_double4 local_point;
	t_double4 local_normal;
	t_mat4x4 transposed_inv;
	t_double4 world_normal;

	inv_transform = mat4x4_inverse(&cylinder->transform);
	local_point = mat4x4_cross_vec(&inv_transform, world_point);
	if (fabs(local_point.y - cylinder->obj.cy.max) < EPSILON)
		vector(&local_normal, 0, 1, 0);
	else if (fabs(local_point.y - cylinder->obj.cy.min) < EPSILON)
		vector(&local_normal, 0, -1, 0);
	else
		vector(&local_normal, local_point.x, 0, local_point.z);
	transposed_inv = mat4x4_transpose(&inv_transform);
	world_normal = mat4x4_cross_vec(&transposed_inv, &local_normal);
	world_normal.w = 0;
	vnormalize(&world_normal);
	return (world_normal);
}

static bool check_caps(t_ray *ray, double t, t_object *cy)
{
	t_double4 point;
	double x, z;

	ray_position(&point, ray, t);
	x = point.x - cy->center.x;
	z = point.z - cy->center.z;
	if (x * x + z * z > cy->obj.cy.radius * cy->obj.cy.radius)
		return (false);
	return (true);
}

static void	intersect_caps(t_ray *ray, t_object *cy, t_intersections *xs)
{
	double	t;

	if (fabs(ray->direction.y) < EPSILON)
		return ;
	t = (cy->obj.cy.min - ray->origin.y) / ray->direction.y;
	if (check_caps(ray, t, cy) && t > EPSILON)
	{
		xs->data[xs->count].object = cy;
		xs->data[xs->count++].t = t;
	}
	t = (cy->obj.cy.max - ray->origin.y) / ray->direction.y;
	if (check_caps(ray, t, cy) && t > EPSILON)
	{
		xs->data[xs->count].object = cy;
		xs->data[xs->count++].t = t;
	}
}

static double	cy_discriminant(t_ray *ray, t_object *cy, double *t_values, t_intersections *xs)
{
	t_double4	oc;
	double		a;
	double		b;
	double		c;
	double		y0;

	oc = ray->origin;
	d4sub(&oc, &oc, &cy->center);
	a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
	if (fabs(a) < EPSILON && cy->obj.cy.closed)
		return (intersect_caps(ray, cy, xs), -1);
	b = 2 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
	c = oc.x * oc.x + oc.z * oc.z - cy->obj.cy.radius * cy->obj.cy.radius;
	t_values[0] = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	t_values[1] = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	y0 = oc.y + t_values[0] * ray->direction.y;
	if (y0 < cy->obj.cy.min || y0 > cy->obj.cy.max)
		t_values[0] = -1;
	y0 = oc.y + t_values[1] * ray->direction.y;
	if (y0 < cy->obj.cy.min || y0 > cy->obj.cy.max)
		t_values[1] = -1;
	return (b * b - 4 * a * c);
}

void intersect_cylinder(t_ray *ray, t_object *cy, t_intersections *xs)
{
	double disc;
	double t_values[MAX_INTERSECTIONS];
	t_mat4x4 inv_transform;
	t_ray transformed_ray;

	inv_transform = mat4x4_inverse(&cy->transform);
	ray->itx.count = 0;
	ray->itx.data->object = cy;
	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(inv_transform));
	disc = cy_discriminant(&transformed_ray, cy, t_values, xs);
	if (disc < 0 || (t_values[0] < 0 && t_values[1] < 0))
		return ;
	if (t_values[0] >= 0)
	{
		xs->data[xs->count].object = cy;
		xs->data[xs->count++].t = t_values[0];
	}
	if (t_values[1] >= 0)
	{
		xs->data[xs->count].object = cy;
		xs->data[xs->count++].t = t_values[1];
	}
	if (cy->obj.cy.closed)
		intersect_caps(&transformed_ray, cy, xs);
}

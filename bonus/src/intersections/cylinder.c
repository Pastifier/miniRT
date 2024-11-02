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

#include "miniRT.h"
#include "macros.h"

t_vec4s cylinder_normal_at(t_obj *cylinder, t_vec4s *world_point)
{
	t_vec4s local_point;
	t_vec4s local_normal;
	t_mat4s transposed_inv;
	t_vec4s world_normal;

	lag_mat4s_cross_vec4s(&cylinder->inv_transform, world_point, &local_point);
	if (fabsf(local_point.y - cylinder->specs.max) < EPSILON)
		lag_vec4sv_init(&local_normal, 0, 1, 0);
	else if (fabsf(local_point.y - cylinder->specs.min) < EPSILON)
		lag_vec4sv_init(&local_normal, 0, -1, 0);
	else
		lag_vec4sv_init(&local_normal, local_point.x, 0, local_point.z);
	lag_mat4s_transpose(&cylinder->inv_transform, &transposed_inv);
	lag_mat4s_cross_vec4s(&transposed_inv, &local_normal, &world_normal);
	world_normal.w = 0;
	lag_vec4s_normalize(&world_normal);
	return (world_normal);
}

static bool check_caps(t_ray *ray, float t, t_obj *cy)
{
	t_vec4s point;
	float x, z;

	ray_position(&point, ray, t);
	x = point.x - cy->center.x;
	z = point.z - cy->center.z;
	if (x * x + z * z > cy->specs.radius * cy->specs.radius)
		return (false);
	return (true);
}

static void	intersect_caps(t_ray *ray, t_obj *cy, t_itx_grp *xs)
{
	float	t;

	if (fabsf(ray->dir.y) < EPSILON)
		return ;
	t = (cy->specs.min - ray->origin.y) / ray->dir.y;
	if (check_caps(ray, t, cy) && t > EPSILON)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t;
	}
	t = (cy->specs.max - ray->origin.y) / ray->dir.y;
	if (check_caps(ray, t, cy) && t > EPSILON)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t;
	}
}

static float	cy_discriminant(t_ray *ray, t_obj *cy, float *t_values, t_itx_grp *xs)
{
	t_vec4s	oc;
	float		a;
	float		b;
	float		c;
	float		y0;

	oc = ray->origin;
	lag_vec4s_sub(&oc, &oc, &cy->center);
	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	if (fabsf(a) < EPSILON && cy->specs.closed)
		return (intersect_caps(ray, cy, xs), -1);
	b = 2 * (oc.x * ray->dir.x + oc.z * ray->dir.z);
	c = oc.x * oc.x + oc.z * oc.z - cy->specs.radius * cy->specs.radius;
	t_values[0] = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	t_values[1] = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	y0 = oc.y + t_values[0] * ray->dir.y;
	if (y0 < cy->specs.min || y0 > cy->specs.max)
		t_values[0] = -1;
	y0 = oc.y + t_values[1] * ray->dir.y;
	if (y0 < cy->specs.min || y0 > cy->specs.max)
		t_values[1] = -1;
	return (b * b - 4 * a * c);
}

void intersect_cylinder(t_ray *ray, t_obj *cy, t_itx_grp *xs)
{
	float disc;
	float t_values[_RT_MAX_ITX];
	t_ray transformed_ray;

	ray->xs.count = 0;
	ray->xs.arr->object = cy;
	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(cy->inv_transform));
	disc = cy_discriminant(&transformed_ray, cy, t_values, xs);
	if (disc < 0 || (t_values[0] < 0 && t_values[1] < 0))
		return ;
	if (t_values[0] >= 0)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[0];
	}
	if (t_values[1] >= 0)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[1];
	}
	if (cy->specs.closed)
		intersect_caps(&transformed_ray, cy, xs);
}

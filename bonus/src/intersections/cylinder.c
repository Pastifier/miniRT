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

t_vec4s cylinder_normal_at(t_obj *cy, t_vec4s *world_point)
{
	t_vec4s local_point;
	t_vec4s local_normal;
	t_vec4s world_normal;

	lag_mat4s_cross_vec4s(&cy->inv_transform, world_point, &local_point);
	if (fabsf(local_point.y - 1.f) < EPSILON)
		lag_vec4sv_init(&local_normal, 0, 1, 0);
	else if (fabsf(local_point.y + 1.f) < EPSILON)
		lag_vec4sv_init(&local_normal, 0, -1, 0);
	else
		lag_vec4sv_init(&local_normal, local_point.x, 0, local_point.z);
	lag_mat4s_cross_vec4s(&cy->transposed_inverse, &local_normal, &world_normal);
	world_normal.w = 0;
	lag_vec4s_normalize(&world_normal);
	return (world_normal);
}

static bool check_caps(t_ray *ray, float t, t_obj *cy)
{
	t_vec4s point;
	(void)cy;
	float x, z;

	ray_position(&point, ray, t);
	x = point.x;
	z = point.z;
	if (x * x + z * z > 1.f)
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
	c = oc.x * oc.x + oc.z * oc.z - 1.f;
	t_values[0] = (-b - sqrt(b * b - 4.f * a * c)) / (2.f * a);
	t_values[1] = (-b + sqrt(b * b - 4.f * a * c)) / (2.f * a);
	y0 = oc.y + t_values[0] * ray->dir.y;
	if (y0 < -1.f || y0 > 1.f)
		t_values[0] = -1.f;
	y0 = oc.y + t_values[1] * ray->dir.y;
	if (y0 < -1.f || y0 > 1.f)
		t_values[1] = -1.f;
	return (b * b - 4.f * a * c);
}

void intersect_cylinder(t_ray *ray, t_obj *cy, t_itx_grp *xs)
{
	float disc;
	float t_values[_RT_MAX_ITX];
	t_ray transformed_ray;

	//ray->xs.count = 0;
	//ray->xs.arr->object = cy;
	transformed_ray = *ray; // EVIL MEMCPY
	ray_transform(&transformed_ray, &(cy->inv_transform));
	disc = cy_discriminant(&transformed_ray, cy, t_values, xs);
	if (disc < 0.f || (t_values[0] < 0.f && t_values[1] < 0.f))
		return ;
	if (t_values[0] >= 0.f)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[0];
	}
	if (t_values[1] >= 0.f)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[1];
	}
	if (cy->specs.closed)
		intersect_caps(&transformed_ray, cy, xs);
}
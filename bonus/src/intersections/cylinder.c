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

t_vec4s	cylinder_normal_at(t_obj *cy, t_vec4s *world_point)
{
	t_vec4s	local_point;
	t_vec4s	local_normal;
	t_vec4s	world_normal;

	lag_mat4s_cross_vec4s(&cy->inv_transform, world_point, &local_point);
	if (fabsf(local_point.y - 1.f) < EPSILON)
		lag_vec4sv_init(&local_normal, 0, 1, 0);
	else if (fabsf(local_point.y + 1.f) < EPSILON)
		lag_vec4sv_init(&local_normal, 0, -1, 0);
	else
		lag_vec4sv_init(&local_normal, local_point.x, 0, local_point.z);
	lag_mat4s_cross_vec4s(&cy->transposed_inverse,
		&local_normal, &world_normal);
	world_normal.w = 0;
	lag_vec4s_normalize(&world_normal);
	return (world_normal);
}

static inline float	cy_discriminant(t_ray *ray, t_obj *cy,
						float *t_values, t_itx_grp *xs)
{
	t_vec4s		oc;
	float		a;
	float		b;
	float		c;
	float		y0;

	oc = ray->origin;
	cy->center.w = 1.f;
	(void)xs;
	lag_vec4s_sub(&oc, &oc, &cy->center);
	a = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	if (fabsf(a) < EPSILON && cy->specs.closed)
		return (-1);
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

bool	intersect_cylinder(t_ray *ray, t_obj *cy, t_itx_grp *xs)
{
	float	disc;
	float	t_values[2];
	t_ray	transformed_ray;
	bool	itx_occured;

	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(cy->inv_transform));
	disc = cy_discriminant(&transformed_ray, cy, t_values, xs);
	itx_occured = false;
	if (disc < EPSILON || (t_values[0] < EPSILON && t_values[1] < EPSILON))
		return (false);
	if (t_values[0] >= EPSILON)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[0];
		itx_occured = true;
	}
	if (t_values[1] >= EPSILON)
	{
		xs->arr[xs->count].object = cy;
		xs->arr[xs->count++].t = t_values[1];
		itx_occured = true;
	}
	return (itx_occured);
}

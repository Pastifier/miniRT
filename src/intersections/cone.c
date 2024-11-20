/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:24:09 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 12:39:07 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

bool	check_cap(t_ray *ray, float t, float radius)
{
	float	x;
	float	z;

	x = ray->origin.x + t * ray->dir.x;
	z = ray->origin.z + t * ray->dir.z;
	(void)radius;
	return (x * x + z * z <= 1.f);
}

t_vec4s	cone_normal_at(t_obj *cone, t_vec4s *world_point)
{
	t_vec4s	local_point;
	t_vec4s	local_normal;
	t_mat4s	transposed_inv;
	t_vec4s	world_normal;
	float	dist;

	lag_mat4s_cross_vec4s(&cone->inv_transform, world_point, &local_point);
	dist = local_point.x * local_point.x + local_point.z * local_point.z;
	if (dist < 1.f * 1.f && local_point.y >= (1.f - EPSILON))
		lag_vec4sv_init(&local_normal, 0, 1, 0);
	else
		lag_vec4sv_init(&local_normal, local_point.x, 0, local_point.z);
	lag_mat4s_transpose(&cone->inv_transform, &transposed_inv);
	lag_mat4s_cross_vec4s(&transposed_inv, &local_normal, &world_normal);
	world_normal.w = 0;
	lag_vec4s_normalize(&world_normal);
	return (world_normal);
}

float	co_discriminant(t_ray transformed_ray, float *t_values)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	sqrt_disc;

	a = powf(transformed_ray.dir.x, 2) - \
		powf(transformed_ray.dir.y, 2) + powf(transformed_ray.dir.z, 2);
	b = 2 * (transformed_ray.origin.x * transformed_ray.dir.x - \
		transformed_ray.origin.y * transformed_ray.dir.y + \
		transformed_ray.origin.z * transformed_ray.dir.z);
	c = powf(transformed_ray.origin.x, 2) - powf(transformed_ray.origin.y, 2);
	disc = b * b - 4 * a * (c + powf(transformed_ray.origin.z, 2));
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

static inline bool	_set_y_values_in_xs(t_ray *transformed_ray,
						t_obj *cone, float *t_vals, t_itx_grp *xs)
{
	bool	itx_occured;
	float	y_vals[2];

	itx_occured = false;
	y_vals[0] = transformed_ray->origin.y + t_vals[0] * transformed_ray->dir.y;
	if (y_vals[0] > -1.f && y_vals[0] < 1.f)
	{
		xs->arr[xs->count].object = cone;
		xs->arr[xs->count++].t = t_vals[0];
		itx_occured = true;
	}
	y_vals[1] = transformed_ray->origin.y + t_vals[1] * transformed_ray->dir.y;
	if (y_vals[1] > -1.f && y_vals[1] < 1.f)
	{
		xs->arr[xs->count].object = cone;
		xs->arr[xs->count++].t = t_vals[1];
		itx_occured = true;
	}
	return (itx_occured);
}

bool	intersect_cone(t_ray *ray, t_obj *cone, t_itx_grp *xs)
{
	t_ray	transformed_ray;
	float	t_values[2];

	transformed_ray = *ray;
	ray_transform(&transformed_ray, &cone->inv_transform);
	if (!co_discriminant(transformed_ray, t_values))
		return (false);
	return (_set_y_values_in_xs(&transformed_ray, cone, t_values, xs));
}

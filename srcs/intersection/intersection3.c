/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:29:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/06 12:57:39by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "linear_algebra.h"

void	swap_doubles(void *a, void *b)
{
	long long	*raw_a;
	long long	*raw_b;

	raw_a = (long long *)a;
	raw_b = (long long *)b;
	*raw_a = *raw_a ^ *raw_b;
	*raw_b = *raw_a ^ *raw_b;
	*raw_a = *raw_a ^ *raw_b;
}

void	dswap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

bool	check_caps(t_ray *ray2, double t)
{
	double	x, z;

	x = ray2->origin.x + (t * ray2->direction.x);
	z = ray2->origin.z + (t * ray2->direction.z);
	x *= x;
	z *= z;
	return ((x + z <= 1));
}

bool	intersect_caps(t_ray *ray2, t_obj *cy, t_intersections *xs)
{
	double	t;
	bool	itx_occured;

	if (!cy->cy_closed || fabs(ray2->direction.y) < EPSILON)
		return (false);
	itx_occured = false;
	t = (cy->cy_min - ray2->origin.y) / ray2->direction.y;
	if (check_caps(ray2, t))
	{
		xs->arr[xs->count].t = t;
		xs->arr[xs->count].obj = cy;
		xs->arr[xs->count].got_hit = true;
		xs->count++;
		itx_occured = true;
	}
	t = (cy->cy_max - ray2->origin.y) / ray2->direction.y;
	if (check_caps(ray2, t))
	{
		xs->arr[xs->count].t = t;
		xs->arr[xs->count].obj = cy;
		xs->arr[xs->count].got_hit = true;
		xs->count++;
		itx_occured = true;
	}
	return (itx_occured);
}

bool	intersect_cylinder(t_ray *r, t_obj *cy, t_intersections *xs)
{
	(void)cy;
	double		a, b, c, disc;
	double		t[2];
	double		y[2];
	t_ray		ray2;
	t_mat4x4	inverse;
	bool		itx_occured;
	t_double4	normalized_dir;

	if (xs->count >= 199)
		return (false);
	vnorm(&normalized_dir, &r->direction);
	t_ray ray_mid = ray(r->origin, normalized_dir);
	inverse = mat4x4_inverse(&cy->transform);
	ray2 = m4r_transform(&ray_mid, &inverse);
	//vnormalize(&ray2.direction);
	a = (ray2.direction.x * ray2.direction.x)
		+ (ray2.direction.z * ray2.direction.z);
	itx_occured = intersect_caps(&ray2, cy, xs);
	if (fabs(a) < EPSILON)
		return (itx_occured);
	b = (2 * ray2.origin.x * ray2.direction.x)
		+ (2 * ray2.origin.z * ray2.direction.z);
	c = -1 + (ray2.origin.x * ray2.origin.x)
		+ (ray2.origin.z * ray2.origin.z);
	disc = (b * b) - (4 * a * c);
	if (disc < 0)
		return (false);
	disc = sqrt(disc);
	t[0] = (-b - disc) / (2.0 * a);
	t[1] = (-b + disc) / (2.0 * a);
	if (t[0] > t[1])
		dswap(&t[0], &t[1]);
	y[0] = ray2.origin.y + t[0] * ray2.direction.y;
	y[1] = ray2.origin.y + t[1] * ray2.direction.y;
	if (cy->cy_min < y[0] && y[0] < cy->cy_max)
	{
		xs->arr[xs->count].t = t[0];
		xs->arr[xs->count].obj = cy;
		xs->arr[xs->count].got_hit = true;
		xs->count++;
		itx_occured = true;
	}
	if (cy->cy_min < y[1] && y[1] < cy->cy_max)
	{
		xs->arr[xs->count].t = t[1];
		xs->arr[xs->count].obj = cy;
		xs->arr[xs->count].got_hit = true;
		xs->count++;
		itx_occured = true;
	}
	return (itx_occured);
}

t_double4	cy_normal_at(t_obj *cy, t_double4 *world_p)
{
	t_double4	local_norm;
	t_double4	world_norm;
	t_double4	local_p;
	double		radial_dist; // radial distance
	t_mat4x4	inverse;
	t_mat4x4	transposed;

	inverse = mat4x4_inverse(&cy->transform);
	local_p = mat4x4_cross_vec(&inverse, world_p);
	radial_dist = (local_p.x * local_p.x) + (local_p.z * local_p.z);
	local_norm = (t_double4){0};
	if (radial_dist < 1 && (local_p.y >= cy->cy_max - EPSILON))
		local_norm.y = 1;
	else if (radial_dist < 1 && (local_p.y <= cy->cy_min + EPSILON))
		local_norm.y = -1;
	else
	{
		vector(&local_norm, local_p.x, 0, local_p.z);
		vnormalize(&local_norm);
	}
	transposed = mat4x4_transpose(&inverse);
	world_norm = mat4x4_cross_vec(&transposed, &local_norm);
	world_norm.w = 0;
	vnormalize(&world_norm);
	return (world_norm);
}

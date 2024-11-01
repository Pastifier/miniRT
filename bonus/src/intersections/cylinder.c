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

// t_vec4s cylinder_normal_at(t_obj *cylinder, t_vec4s *world_point)
// {
// 	t_vec4s local_point;
// 	t_vec4s local_normal;
// 	t_mat4s transposed_inv;
// 	t_vec4s world_normal;

// 	local_point = lag_mat4s_cross_vec4s(cylinder->inv_transform, *world_point);
// 	if (fabsf(local_point.y - cylinder->obj.cy.max) < EPSILON)
// 		lag_vec4sv_init(&local_normal, 0, 1, 0);
// 	else if (fabsf(local_point.y - cylinder->obj.cy.min) < EPSILON)
// 		lag_vec4sv_init(&local_normal, 0, -1, 0);
// 	else
// 		lag_vec4sv_init(&local_normal, local_point.x, 0, local_point.z);
// 	transposed_inv = lag_mat4s_transpose_ret(&cylinder->inv_transform);
// 	world_normal = lag_mat4s_cross_vec4s(transposed_inv, local_normal);
// 	world_normal.w = 0;
// 	lag_vec4s_normalize(&world_normal);
// 	return (world_normal);
// }

// static bool check_caps(t_ray *ray, double t, t_obj *cy)
// {
// 	t_vec4s point;
// 	double x, z;

// 	ray_position(&point, ray, t);
// 	x = point.x - cy->center.x;
// 	z = point.z - cy->center.z;
// 	if (x * x + z * z > cy->obj.cy.radius * cy->obj.cy.radius)
// 		return (false);
// 	return (true);
// }

// static void	intersect_caps(t_ray *ray, t_obj *cy, t_itx *xs)
// {
// 	double	t;

// 	if (fabsf(ray->direction.y) < EPSILON)
// 		return ;
// 	t = (cy->obj.cy.min - ray->origin.y) / ray->direction.y;
// 	if (check_caps(ray, t, cy) && t > EPSILON)
// 	{
// 		xs->arr[xs->count].object = cy;
// 		xs->arr[xs->count++].t = t;
// 	}
// 	t = (cy->obj.cy.max - ray->origin.y) / ray->direction.y;
// 	if (check_caps(ray, t, cy) && t > EPSILON)
// 	{
// 		xs->arr[xs->count].object = cy;
// 		xs->arr[xs->count++].t = t;
// 	}
// }

// static double	cy_discriminant(t_ray *ray, t_obj *cy, double *t_values, t_itx *xs)
// {
// 	t_vec4s	oc;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		y0;

// 	oc = ray->origin;
// 	d4sub(&oc, &oc, &cy->center);
// 	a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
// 	if (fabsf(a) < EPSILON && cy->obj.cy.closed)
// 		return (intersect_caps(ray, cy, xs), -1);
// 	b = 2 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
// 	c = oc.x * oc.x + oc.z * oc.z - cy->obj.cy.radius * cy->obj.cy.radius;
// 	t_values[0] = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
// 	t_values[1] = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
// 	y0 = oc.y + t_values[0] * ray->direction.y;
// 	if (y0 < cy->obj.cy.min || y0 > cy->obj.cy.max)
// 		t_values[0] = -1;
// 	y0 = oc.y + t_values[1] * ray->direction.y;
// 	if (y0 < cy->obj.cy.min || y0 > cy->obj.cy.max)
// 		t_values[1] = -1;
// 	return (b * b - 4 * a * c);
// }

// void intersect_cylinder(t_ray *ray, t_obj *cy, t_itx *xs)
// {
// 	double disc;
// 	double t_values[MAX_INTERSECTIONS];
// 	t_ray transformed_ray;

// 	ray->itx.count = 0;
// 	ray->itx.arr->object = cy;
// 	transformed_ray = *ray;
// 	ray_transform(&transformed_ray, &(cy->inv_transform));
// 	disc = cy_discriminant(&transformed_ray, cy, t_values, xs);
// 	if (disc < 0 || (t_values[0] < 0 && t_values[1] < 0))
// 		return ;
// 	if (t_values[0] >= 0)
// 	{
// 		xs->arr[xs->count].object = cy;
// 		xs->arr[xs->count++].t = t_values[0];
// 	}
// 	if (t_values[1] >= 0)
// 	{
// 		xs->arr[xs->count].object = cy;
// 		xs->arr[xs->count++].t = t_values[1];
// 	}
// 	if (cy->obj.cy.closed)
// 		intersect_caps(&transformed_ray, cy, xs);
// }

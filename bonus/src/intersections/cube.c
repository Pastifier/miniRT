/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:05:59 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/23 11:30:05 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

// void cube(t_object *cube, t_double4 *center, double length, t_mat4x4 *transform)
// {
// 	cube->type = OBJ_CUBE;
// 	if (center)
// 		cube->center = *center;
// 	else
// 		point(&cube->center, 0.0, 0.0, 0.0);
// 	if (transform)
// 		cube->transform = *transform;
// 	else
// 		cube->transform = mat4x4_identity();
// 	cube->obj.cube.side_length = length;
// 	cube->material = default_material();
// }

// static void check_axis(double origin, double direction, double side_length, t_double2 *t)
// {
// 	double half_side;
// 	double tmin_numerator;
// 	double tmax_numerator;
// 	double temp;

// 	half_side = side_length / 2.0;
// 	tmin_numerator = (-half_side - origin);
// 	tmax_numerator = (half_side - origin);
// 	if (fabs(direction) >= EPSILON)
// 	{
// 		t->x = tmin_numerator / direction;
// 		t->y = tmax_numerator / direction;
// 	}
// 	else
// 	{
// 		t->x = tmin_numerator * INFINITY;
// 		t->y = tmax_numerator * INFINITY;
// 	}
// 	if (t->x > t->y)
// 	{
// 		temp = t->x;
// 		t->x = t->y;
// 		t->y = temp;
// 	}
// }

// void intersect_cube(t_ray *ray, t_object *cube, t_intersections *xs)
// {
// 	t_mat4x4 inv_transform;
// 	t_ray transformed_ray;
// 	t_double2 xt;
// 	t_double2 yt;
// 	t_double2 zt;
// 	t_double2 t;

// 	inv_transform = mat4x4_inverse(&cube->transform);
// 	transformed_ray = *ray;
// 	ray_transform(&transformed_ray, &(inv_transform));

// 	check_axis(transformed_ray.origin.x, transformed_ray.direction.x, cube->obj.cube.side_length, &xt);
// 	check_axis(transformed_ray.origin.y, transformed_ray.direction.y, cube->obj.cube.side_length, &yt);
// 	check_axis(transformed_ray.origin.z, transformed_ray.direction.z, cube->obj.cube.side_length, &zt);

// 	t.x = fmax(fmax(xt.x, yt.x), zt.x);
// 	t.y = fmin(fmin(xt.y, yt.y), zt.y);

// 	if (t.x > t.y)
// 		return;
// 	xs->data[xs->count].object = cube;
// 	xs->data[xs->count++].t = t.x;
// 	xs->data[xs->count].object = cube;
// 	xs->data[xs->count++].t = t.y;
// }

// t_double4 cube_normal_at(t_object *cube, t_double4 *world_point)
// {
// 	t_double4	object_n_p[2];
// 	t_double4	world_normal;
// 	t_mat4x4	inv_transform;
// 	double		maxc;

// 	inv_transform = mat4x4_inverse(&cube->transform);
// 	object_n_p[1] = mat4x4_cross_vec(&inv_transform, world_point);

// 	maxc = fmax(fmax(fabs(object_n_p[1].x), fabs(object_n_p[1].y)), fabs(object_n_p[1].z));

// 	if (maxc == fabs(object_n_p[1].x))
// 		vector(&world_normal, object_n_p[1].x, 0, 0);
// 	else if (maxc == fabs(object_n_p[1].y))
// 		vector(&world_normal, 0, object_n_p[1].y, 0);
// 	else
// 		vector(&world_normal, 0, 0, object_n_p[1].z);
// 	vnormalize(&world_normal);
// 	return (world_normal);
// }

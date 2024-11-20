/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:57:02 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/20 11:07:08 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static void	check_axis(float origin, float dir, float side_length, t_vec4s *t)
{
	float	half_side;
	float	tmin_numerator;
	float	tmax_numerator;
	float	temp;

	half_side = side_length / 2.0;
	tmin_numerator = (-half_side - origin);
	tmax_numerator = (half_side - origin);
	if (fabsf(dir) >= EPSILON)
	{
		t->x = tmin_numerator / dir;
		t->y = tmax_numerator / dir;
	}
	else
	{
		t->x = tmin_numerator * INFINITY;
		t->y = tmax_numerator * INFINITY;
	}
	if (t->x > t->y)
	{
		temp = t->x;
		t->x = t->y;
		t->y = temp;
	}
}

static inline void	_check_axes(t_ray *transformed_ray, t_obj *cube,
						t_mat4s *xyz_t)
{
	check_axis(transformed_ray->origin.x, transformed_ray->dir.x,
		cube->specs.side_length, &xyz_t->r1);
	check_axis(transformed_ray->origin.y, transformed_ray->dir.y,
		cube->specs.side_length, &xyz_t->r2);
	check_axis(transformed_ray->origin.z, transformed_ray->dir.z,
		cube->specs.side_length, &xyz_t->r3);
}

bool	intersect_cube(t_ray *ray, t_obj *cube, t_itx_grp *xs)
{
	t_ray	transformed_ray;
	t_mat4s	xyz_t;
	t_vec4s	t;

	transformed_ray = *ray;
	ray_transform(&transformed_ray, &(cube->inv_transform));
	_check_axes(&transformed_ray, cube, &xyz_t);
	t.x = fmax(fmax(xyz_t.r1.x, xyz_t.r2.x), xyz_t.r3.x);
	t.y = fmin(fmin(xyz_t.r1.y, xyz_t.r2.y), xyz_t.r3.y);
	if (t.x > t.y)
		return (false);
	xs->arr[xs->count].object = cube;
	xs->arr[xs->count++].t = t.x;
	xs->arr[xs->count].object = cube;
	xs->arr[xs->count++].t = t.y;
	return (true);
}

t_vec4s	cube_normal_at(t_obj *cube, t_vec4s *world_point)
{
	t_vec4s		object_n_p[2];
	t_vec4s		world_normal;
	t_vec4s		abslocal_n;
	float		maxc;

	lag_mat4s_cross_vec4s(&cube->inv_transform, world_point, &object_n_p[1]);
	abslocal_n.x = fabsf(object_n_p[1].x);
	abslocal_n.y = fabsf(object_n_p[1].y);
	abslocal_n.z = fabsf(object_n_p[1].z);
	maxc = fmax(fmax(abslocal_n.x, abslocal_n.y), abslocal_n.z);
	if (maxc == fabsf(object_n_p[1].x))
		lag_vec4sv_init(&world_normal, object_n_p[1].x, 0, 0);
	else if (maxc == fabsf(object_n_p[1].y))
		lag_vec4sv_init(&world_normal, 0, object_n_p[1].y, 0);
	else
		lag_vec4sv_init(&world_normal, 0, 0, object_n_p[1].z);
	lag_mat4s_cross_vec4s(&cube->transposed_inverse, &world_normal, &world_normal);
	lag_vec4s_normalize(&world_normal);
	world_normal.w = 0.f;
	return (world_normal);
}

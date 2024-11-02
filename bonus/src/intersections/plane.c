/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:39 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/02 22:55:31 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_vec4s	plane_normal_at(t_obj *plane)
{
	t_vec4s	normal;
	t_mat4s	inv_transpose;

	lag_mat4s_transpose(&plane->inv_transform, &inv_transpose);
	lag_mat4s_cross_vec4s(&inv_transpose, &plane->orientation, &normal);
	normal.w = 0;
	lag_vec4s_normalize(&normal);
	return (normal);
}

void	intersect_plane(t_ray *ray, t_obj *plane, t_itx_grp *xs)
{
	t_vec4s		plane_to_ray;
	t_vec4s		plane_normal;
	t_ray		trans_ray;
	float		denom;
	float		t;

	//Ditch the plane_normal_at() function and just prep the normal during parsing and save it.
	plane_normal = plane_normal_at(plane);
	ray->xs.arr[xs->count].object = plane;
	trans_ray = *ray;
	ray_transform(&trans_ray, &plane->inv_transform);
	denom = lag_vec4s_dot_ret(&plane_normal, &trans_ray.dir);
	//Using fabs to get the floating point absolute number so that if denom is a small negative number,
	//it will still be considered 0 and avoid intersecting with rays parallel to the plane
	if (fabsf(denom) <= EPSILON)
		return ;
	lag_vec4s_sub(&plane_to_ray, &plane->center, &trans_ray.origin);
	t = lag_vec4s_dot_ret(&plane_to_ray, &plane_normal) / denom;
	if (t > EPSILON)
	{
		xs->arr[xs->count].object = plane;
		xs->arr[xs->count++].t = t;
	}
}

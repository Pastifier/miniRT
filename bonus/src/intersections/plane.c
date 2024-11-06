/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:39 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/06 13:55:22 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_vec4s	plane_normal_at(t_obj *plane)
{
	t_vec4s	local_normal;

	lag_mat4s_cross_vec4s(&plane->transposed_inverse, &plane->orientation, &local_normal);
	local_normal.w = 0;
	lag_vec4s_normalize(&local_normal);
	return (local_normal);
}

void	intersect_plane(t_ray *ray, t_obj *plane, t_itx_grp *xs)
{
	t_vec4s		plane_normal;
	t_ray		trans_ray;
	float		denom;
	float		t;

	plane_normal = plane_normal_at(plane);
	trans_ray = *ray; // BAD_MEMCPY
	ray_transform(&trans_ray, &plane->inv_transform);
	if (fabsf(trans_ray.dir.y) < EPSILON)
		return ;
	denom = trans_ray.dir.y;
	t = -trans_ray.origin.y / denom;
	if (t > EPSILON)
	{
		xs->arr[xs->count].object = plane;
		xs->arr[xs->count++].t = t;
	}
}

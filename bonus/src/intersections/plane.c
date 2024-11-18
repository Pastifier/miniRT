/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:39 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/18 14:38:17 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

bool	intersect_plane(t_ray *ray, t_obj *plane, t_itx_grp *xs)
{
	t_ray		trans_ray;
	float		denom;
	float		t;

	trans_ray = *ray;
	ray_transform(&trans_ray, &plane->inv_transform);
	if (fabsf(trans_ray.dir.y) < EPSILON)
		return (false);
	denom = trans_ray.dir.y;
	t = -trans_ray.origin.y / denom;
	if (t > EPSILON)
	{
		xs->arr[xs->count].object = plane;
		xs->arr[xs->count++].t = t;
		return (true);
	}
	return (false);
}

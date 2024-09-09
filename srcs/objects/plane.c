/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:39 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/09 13:48:40 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"

void plane(t_object *plane, t_double4 *center, t_mat4x4 *transform)
{
	plane->type = OBJ_PLANE;
	if (center)
		plane->center = *center;
	else
		point(&plane->center, 0.0, 0.0, 0.0);
	if (transform)
		plane->transform = *transform;
	else
		plane->transform = mat4x4_identity();
	vector(&plane->obj.plane.normal, 0.0, 1.0, 0.0);
	plane->material = default_material();
}

t_double4	plane_normal_at(t_object *plane)
{
	t_double4	normal;
	t_mat4x4	inv_transform;
	t_mat4x4	inv_transpose;

	inv_transform = mat4x4_inverse(&plane->transform);
	inv_transpose = mat4x4_transpose(&inv_transform);
	normal = mat4x4_cross_vec(&inv_transpose, &plane->obj.plane.normal);
	normal.w = 0;
	vnormalize(&normal);
	return (normal);
}

void	intersect_plane(t_ray *ray, t_object *plane)
{
	t_double4	plane_to_ray;
	t_double4	plane_normal;
	t_ray		trans_ray;
	t_mat4x4	inv_transform;
	double		denom;
	double		t;

	plane_normal = plane_normal_at(plane);
	ray->itx.data->object = plane;
	trans_ray = *ray;
	inv_transform = mat4x4_inverse(&plane->transform);
	ray_transform(&trans_ray, &inv_transform);
	denom = vdot(&plane_normal, &trans_ray.direction);
	//Using fabs to get the floating point absolute number so that if denom is a small negative number,
	//it will still be considered 0 and avoid intersecting with rays parallel to the plane
	if (fabs(denom) <= EPSILON)
		return ;
	d4sub(&plane_to_ray, &plane->center, &trans_ray.origin);
	t = vdot(&plane_to_ray, &plane_normal) / denom;
	if (t > EPSILON)
	{
		ray->itx.count = 1;
		ray->itx.data[0].t = t;
		ray->itx.data[0].object = plane;
	}
}

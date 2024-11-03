/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:07:20 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/03 08:18:46 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_vec4s	sphere_normal_at(t_obj *sphere, t_vec4s *world_p)
{
	t_vec4s	local_p;
	t_vec4s	local_n;
	t_vec4s	world_n;

	lag_mat4s_cross_vec4s(&sphere->inv_transform, world_p, &local_p);
	lag_vec4s_sub(&local_n, &local_p, &sphere->trans);
	lag_mat4s_cross_vec4s(&sphere->transposed_inverse, &local_n, &world_n);
	world_n.w = 0.f;
	lag_vec4s_normalize(&world_n);
	return (world_n);
}

void	intersect_sphere(t_ray *r, t_obj *sphere, t_itx_grp *xs)
{
	float	d;
	t_ray	trans_r;
	t_vec4s	sphere_to_ray;
	t_vec4s	abc;

	if (xs->count + 2 >= _RT_MAX_ITX)
		return ;
	trans_r = *r;
	ray_transform(&trans_r, &sphere->inv_transform);
	lag_vec4s_sub(&sphere_to_ray, &trans_r.origin, &sphere->trans);
	abc.x = lag_vec4s_dot_ret(&trans_r.dir, &trans_r.dir);
	abc.y = 2.0f * lag_vec4s_dot_ret(&sphere_to_ray, &trans_r.dir);
	abc.z = lag_vec4s_dot_ret(&sphere_to_ray, &sphere_to_ray)
		- 1; //(sphere->specs.radius * sphere->specs.radius);
	d = abc.y * abc.y - 4.f * abc.x * abc.z;
	if (d < 0)
		return ;
	d = sqrtf(d);
	xs->arr[xs->count].object = sphere;
	xs->arr[xs->count++].t = (-abc.y - d) / (2.f * abc.x);
	xs->arr[xs->count].object = sphere;
	xs->arr[xs->count++].t = (-abc.y + d) / (2.f * abc.x);
}

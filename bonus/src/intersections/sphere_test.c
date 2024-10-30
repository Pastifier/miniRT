/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:07:20 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/30 11:36:56 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_mat4s	lag_mat4s_transpose_ret(const t_mat4s m)
{
	t_mat4s			ret0;
	const __m128	tmp0 = _mm_unpacklo_ps(m.r1.simd, m.r2.simd);
	const __m128	tmp1 = _mm_unpacklo_ps(m.r3.simd, m.r4.simd);
	const __m128	tmp2 = _mm_unpackhi_ps(m.r1.simd, m.r2.simd);
	const __m128	tmp3 = _mm_unpackhi_ps(m.r3.simd, m.r4.simd);

	ret0.r1.simd = _mm_movelh_ps(tmp0, tmp1);
	ret0.r2.simd = _mm_movehl_ps(tmp1, tmp0);
	ret0.r3.simd = _mm_movelh_ps(tmp2, tmp3);
	ret0.r4.simd = _mm_movehl_ps(tmp3, tmp2);
	return (ret0);
}

t_vec4s	sphere_normal_at(t_obj *sphere, t_vec4s *world_p)
{
	t_vec4s	local_p;
	t_vec4s	local_n;
	t_vec4s	world_n;
	t_mat4s	transposed_inv;

	local_p = lag_mat4s_cross_vec4s(sphere->inv_transform, *world_p);
	lag_vec4s_sub(&local_n, local_p, sphere->trans);
	transposed_inv = lag_mat4s_transpose_ret(sphere->inv_transform);
	world_n = lag_mat4s_cross_vec4s(transposed_inv, local_n);
	world_n.w = 0;
	world_n = lag_vec4s_normalize_ret(world_n);
	return (world_n);
}

void	intersect_sphere(t_ray *r, t_obj *sphere, t_itx_grp *xs)
{
	float	d;
	t_ray	trans_r;
	t_vec4s	sphere_to_ray;

	if (xs->count + 2 >= _RT_MAX_ITX)
		return ;
	trans_r = *r;
	ray_transform(&trans_r, &sphere->inv_transform);
	lag_vec4s_sub(&sphere_to_ray, trans_r.origin, sphere->trans);
	sphere->specs.a = lag_vec4s_dot_ret(trans_r.dir, trans_r.dir);
	sphere->specs.b = 2.0 * lag_vec4s_dot_ret(sphere_to_ray, trans_r.dir);
	sphere->specs.c = lag_vec4s_dot_ret(sphere_to_ray, sphere_to_ray)
		- (sphere->specs.radius * sphere->specs.radius);
	d = powf(sphere->specs.b, 2) - 4.f * sphere->specs.a * sphere->specs.c;
	if (d < 0)
		return ;
	d = sqrtf(d);
	xs->arr[xs->count].object = sphere;
	xs->arr[xs->count++].t = (-sphere->specs.b - d) / (2.f * sphere->specs.a);
	xs->arr[xs->count].object = sphere;
	xs->arr[xs->count++].t = (-sphere->specs.b + d) / (2.f * sphere->specs.a);
}

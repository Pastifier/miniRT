/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_init_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:08:59 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 10:15:20 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

t_mat4s	lag_mat4s_rotation_x(float rad)
{
	t_mat4s	ret;

	ret.r1.simd = _mm_set_ps(0.f, 0.f, 0.f, 1.f);
	ret.r2.simd = _mm_set_ps(0.f, -sinf(rad), cosf(rad), 0.f);
	ret.r3.simd = _mm_set_ps(0.f, cosf(rad), sinf(rad), 0.f);
	ret.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	return (ret);
}

t_mat4s	lag_mat4s_rotation_y(float rad)
{
	t_mat4s	ret;

	ret.r1.simd = _mm_set_ps(0.f, sinf(rad), 0.f, cosf(rad));
	ret.r2.simd = _mm_set_ps(0.f, 0.f, 1.f, 0.f);
	ret.r3.simd = _mm_set_ps(0.f, cosf(rad), 0.f, -sinf(rad));
	ret.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	return (ret);
}

t_mat4s	lag_mat4s_rotation_z(float rad)
{
	t_mat4s	ret;

	ret.r1.simd = _mm_set_ps(0.f, 0.f, -sinf(rad), cosf(rad));
	ret.r2.simd = _mm_set_ps(0.f, 0.f, cosf(rad), sinf(rad));
	ret.r3.simd = _mm_set_ps(0.f, 1.f, 0.f, 0.f);
	ret.r4.simd = _mm_set_ps(1.f, 0.f, 0.f, 0.f);
	return (ret);
}

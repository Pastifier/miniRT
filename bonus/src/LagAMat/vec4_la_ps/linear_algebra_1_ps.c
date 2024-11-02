/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_1_ps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:27:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 07:15:28 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	lag_vec4s_dot(float *out, const t_vec4s in1,
						const t_vec4s in2)
{
	*out = _mm_cvtss_f32(_mm_dp_ps(in1.simd, in2.simd, 0xF1));
}

float	lag_vec4s_dot_ret(const t_vec4s in1,
							const t_vec4s in2)
{
	return (_mm_cvtss_f32(_mm_dp_ps(in1.simd, in2.simd, 0xF1)));
}

void	lag_vec4s_magnitude(float *out, const t_vec4s in)
{
	const __m128	mul0 = _mm_dp_ps(in.simd, in.simd, 0xF1);
	const __m128	sqt0 = _mm_sqrt_ps(mul0);

	*out = _mm_cvtss_f32(sqt0);
}

float	lag_vec4s_magnitude_ret(const t_vec4s in)
{
	const __m128	mul0 = _mm_dp_ps(in.simd, in.simd, 0xF1);
	const __m128	sqt0 = _mm_sqrt_ps(mul0);

	return(_mm_cvtss_f32(sqt0));
}

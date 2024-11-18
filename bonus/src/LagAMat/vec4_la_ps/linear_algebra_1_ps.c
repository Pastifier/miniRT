/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra_1_ps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 01:27:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 10:22:16 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	lag_vec4s_dot(float *out, const t_vec4s *in1, const t_vec4s *in2)
{
	__m128	mul;
	__m128	shuf1;
	__m128	sums;
	__m128	shuf2;

	mul = _mm_mul_ps(in1->simd, in2->simd);
	shuf1 = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
	sums = _mm_add_ps(mul, shuf1);
	shuf2 = _mm_shuffle_ps(sums, sums, _MM_SHUFFLE(1, 0, 3, 2));
	sums = _mm_add_ss(sums, shuf2);
	*out = _mm_cvtss_f32(sums);
}

float	lag_vec4s_dot_ret(const t_vec4s *in1,
							const t_vec4s *in2)
{
	return (_mm_cvtss_f32(_mm_dp_ps(in1->simd, in2->simd, 0xF1)));
}

static inline __m128	_mm_msqr_ps(const __m128 vec)
{
	__m128	mul;
	__m128	shuf;
	__m128	sums;

	mul = _mm_mul_ps(vec, vec);
	shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
	sums = _mm_add_ps(mul, shuf);
	shuf = _mm_movehl_ps(shuf, sums);
	sums = _mm_add_ss(sums, shuf);
	return (_mm_shuffle_ps(sums, sums, _MM_SHUFFLE(0, 0, 0, 0)));
}

void	lag_vec4s_magnitude(float *out, const t_vec4s in)
{
	const __m128	mul0 = _mm_dp_ps(in.simd, in.simd, 0xF1);
	const __m128	sqt0 = _mm_sqrt_ps(mul0);

	*out = _mm_cvtss_f32(sqt0);
}

float	lag_vec4s_magnitude_ret(const t_vec4s in)
{
	const __m128	mul0 = _mm_msqr_ps(in.simd);
	const __m128	sqt0 = _mm_sqrt_ps(mul0);

	return (_mm_cvtss_f32(sqt0));
}

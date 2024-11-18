/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_cross.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 09:44:27 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 10:11:53 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ltypes.h"

/// @brief Returns the cross product of a `t_mat4s` with a `t_vec4s`
///        (in that order).
void	lag_mat4s_cross_vec4s(const t_mat4s *m,
							const t_vec4s *v, t_vec4s *out)
{
	const __m128	mul0 = _mm_mul_ps(m->simd[0], v->simd);
	const __m128	mul1 = _mm_mul_ps(m->simd[1], v->simd);
	const __m128	mul2 = _mm_mul_ps(m->simd[2], v->simd);
	const __m128	mul3 = _mm_mul_ps(m->simd[3], v->simd);

	out->simd = _mm_hadd_ps(_mm_hadd_ps(mul0, mul1),
			_mm_hadd_ps(mul2, mul3));
}

static inline void	lag_mat4s_cross_stage1(const t_mat4s in1,
						const t_mat4s in2, __m256 *c)
{
	__m256	a[2];
	__m256	b[1];
	__m256	t[2];
	__m256	u[2];

	t[0] = in1._ymm[0];
	t[1] = in1._ymm[1];
	u[0] = in2._ymm[0];
	a[0] = _mm256_shuffle_ps(t[0], t[0], _MM_SHUFFLE(0, 0, 0, 0));
	a[1] = _mm256_shuffle_ps(t[1], t[1], _MM_SHUFFLE(0, 0, 0, 0));
	b[0] = _mm256_permute2f128_ps(u[0], u[0], 0x00);
	c[0] = _mm256_mul_ps(a[0], b[0]);
	c[1] = _mm256_mul_ps(a[1], b[0]);
	a[0] = _mm256_shuffle_ps(t[0], t[0], _MM_SHUFFLE(1, 1, 1, 1));
	a[1] = _mm256_shuffle_ps(t[1], t[1], _MM_SHUFFLE(1, 1, 1, 1));
	b[0] = _mm256_permute2f128_ps(u[0], u[0], 0x11);
	c[2] = _mm256_mul_ps(a[0], b[0]);
	c[3] = _mm256_mul_ps(a[1], b[0]);
}

static inline void	lag_mat4s_cross_stage2(const t_mat4s in1,
						const t_mat4s in2, __m256 *c)
{
	__m256	a[2];
	__m256	b[1];
	__m256	t[2];
	__m256	u[2];

	t[0] = in1._ymm[0];
	t[1] = in1._ymm[1];
	u[1] = in2._ymm[1];
	a[0] = _mm256_shuffle_ps(t[0], t[0], _MM_SHUFFLE(2, 2, 2, 2));
	a[1] = _mm256_shuffle_ps(t[1], t[1], _MM_SHUFFLE(2, 2, 2, 2));
	b[0] = _mm256_permute2f128_ps(u[1], u[1], 0x00);
	c[4] = _mm256_mul_ps(a[0], b[0]);
	c[5] = _mm256_mul_ps(a[1], b[0]);
	a[0] = _mm256_shuffle_ps(t[0], t[0], _MM_SHUFFLE(3, 3, 3, 3));
	a[1] = _mm256_shuffle_ps(t[1], t[1], _MM_SHUFFLE(3, 3, 3, 3));
	b[0] = _mm256_permute2f128_ps(u[1], u[1], 0x11);
	c[6] = _mm256_mul_ps(a[0], b[0]);
	c[7] = _mm256_mul_ps(a[1], b[0]);
	c[0] = _mm256_add_ps(c[0], c[2]);
	c[4] = _mm256_add_ps(c[4], c[6]);
	c[1] = _mm256_add_ps(c[1], c[3]);
	c[5] = _mm256_add_ps(c[5], c[7]);
}

/// @brief computes the cross product of `in1` with `in2`
///        (in that order), and stores the result in the `t_mat4s`
///        pointed-to by `out`.
void	lag_mat4s_cross_mat4s(const t_mat4s in1,
						const t_mat4s in2, t_mat4s *out)
{
	__m256	c[8];

	lag_mat4s_cross_stage1(in1, in2, c);
	lag_mat4s_cross_stage2(in1, in2, c);
	out->_ymm[0] = _mm256_add_ps(c[0], c[4]);
	out->_ymm[1] = _mm256_add_ps(c[1], c[5]);
}

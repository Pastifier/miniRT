/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_transform_inverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:34:23 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 10:19:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

/// @brief Calculates the inverse of a decomposed matrix
/// (rotation, scale, translation)
/// @param rot The rotational component of the matrix
/// @param s The scale factor of the matrix
/// @param t The translation component of the matrix
/// @return The inverse of the decomposed matrix
/// @warning The scale should NOT contain any zero components as that will
/// cause divide-by-zero errors! (And it doesn't really make sense anyway)
t_mat4s	lag_mat4s_get_transform_inverse(const t_mat4s rot, const __m128 s,
			const __m128 t)
{
	t_mat4s			ret0;
	__m128			tmp[4];
	const __m128	rcps = _mm_div_ps(_mm_set1_ps(1.f), s);
	const __m128	tinv = _mm_sub_ps(_mm_set1_ps(0.f), t);

	tmp[0] = _mm_unpacklo_ps(rot.simd[0], rot.simd[1]);
	tmp[1] = _mm_unpackhi_ps(rot.simd[0], rot.simd[1]);
	tmp[2] = _mm_unpacklo_ps(rot.simd[2], rot.simd[3]);
	tmp[3] = _mm_unpackhi_ps(rot.simd[2], rot.simd[3]);
	ret0.simd[0] = _mm_movelh_ps(tmp[0], tmp[2]);
	ret0.simd[1] = _mm_movehl_ps(tmp[2], tmp[0]);
	ret0.simd[2] = _mm_movelh_ps(tmp[1], tmp[3]);
	ret0.simd[3] = _mm_set_ps(1, 0, 0, 0);
	ret0.simd[0] = _mm_mul_ps(ret0.simd[0],
			_mm_shuffle_ps(rcps, rcps, _MM_SHUFFLE(0, 0, 0, 0)));
	ret0.simd[1] = _mm_mul_ps(ret0.simd[1],
			_mm_shuffle_ps(rcps, rcps, _MM_SHUFFLE(1, 1, 1, 1)));
	ret0.simd[2] = _mm_mul_ps(ret0.simd[2],
			_mm_shuffle_ps(rcps, rcps, _MM_SHUFFLE(2, 2, 2, 2)));
	ret0.r1.w = _mm_cvtss_f32(_mm_dp_ps(ret0.simd[0], tinv, 0xF1));
	ret0.r2.w = _mm_cvtss_f32(_mm_dp_ps(ret0.simd[1], tinv, 0xF1));
	ret0.r3.w = _mm_cvtss_f32(_mm_dp_ps(ret0.simd[2], tinv, 0xF1));
	return (ret0);
}

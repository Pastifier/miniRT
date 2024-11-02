/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat4s_transform_inverse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:34:23 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 10:07:22 by ebinjama         ###   ########.fr       */
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
/// cause a floating-point exception.
t_mat4s lag_mat4s_get_transform_inverse(const t_mat4s rot, const __m128 s,
			const __m128 t)
{
	const __m128	rcps = _mm_div_ps(_mm_set1_ps(1.f), s);
	const __m128	tinv = _mm_sub_ps(_mm_set1_ps(0.f), t);
	__m128			tmp0, tmp1, tmp2, tmp3;
	t_mat4s			ret0;
	t_vec4s			trns;

	ret0.simd[0] = _mm_mul_ps(rot.simd[0], rcps);
	ret0.simd[1] = _mm_mul_ps(rot.simd[1], rcps);
	ret0.simd[2] = _mm_mul_ps(rot.simd[2], rcps);
	tmp0 = _mm_unpacklo_ps(ret0.simd[0], ret0.simd[1]);			  // [r00, r10, r01, r11]
	tmp1 = _mm_unpackhi_ps(ret0.simd[0], ret0.simd[1]);			  // [r02, r12, r03, r13]
	tmp2 = _mm_unpacklo_ps(ret0.simd[2], _mm_set_ps(0, 0, 0, 1)); // [r20, r30, 0, 1]
	tmp3 = _mm_unpackhi_ps(ret0.simd[2], _mm_set_ps(0, 0, 0, 1)); // [r22, r32, 0, 1]
	ret0.simd[0] = _mm_movelh_ps(tmp0, tmp2); // First row after transposition
	ret0.simd[1] = _mm_movehl_ps(tmp2, tmp0); // Second row after transposition
	ret0.simd[2] = _mm_movelh_ps(tmp1, tmp3); // Third row after transposition
	ret0.simd[3] = _mm_set_ps(1, 0, 0, 0);	  // Set last row as [0, 0, 0, 1] for homogenous coordinates
	trns.simd = _mm_add_ps(
		_mm_add_ps(
			_mm_mul_ps(ret0.simd[0], _mm_shuffle_ps(tinv, tinv, _MM_SHUFFLE(0, 0, 0, 0))),
			_mm_mul_ps(ret0.simd[1], _mm_shuffle_ps(tinv, tinv, _MM_SHUFFLE(1, 1, 1, 1)))),
		_mm_mul_ps(ret0.simd[2], _mm_shuffle_ps(tinv, tinv, _MM_SHUFFLE(2, 2, 2, 2))));
	ret0.simd[0] = _mm_insert_ps(ret0.simd[0], trns.simd, 0x30); // x-component of translation
	ret0.simd[1] = _mm_insert_ps(ret0.simd[1], trns.simd, 0x30); // y-component of translation
	ret0.simd[2] = _mm_insert_ps(ret0.simd[2], trns.simd, 0x30); // z-component of translation

	return (ret0);
}

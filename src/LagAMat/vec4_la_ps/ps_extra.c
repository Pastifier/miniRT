/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 06:45:19 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 10:24:52 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

t_vec4s	lag_vec4s_normalize_mediump(const t_vec4s in)
{
	const __m128	msqr = _mm_dp_ps(in.simd, in.simd, 0xFF);
	__m128			sqrt;

	if (_mm_cvtss_f32(msqr) == 0.0f)
		return ((t_vec4s){.simd = _mm_set1_ps(0.f)});
	sqrt = _mm_sqrt_ps(msqr);
	return ((t_vec4s)
		{
			.simd = _mm_mul_ps(in.simd, _mm_rcp_ps(sqrt))
		});
}

t_vec4s	lag_vec4s_normalize_highp(const t_vec4s in)
{
	const __m128	msqr = _mm_dp_ps(in.simd, in.simd, 0xFF);
	__m128			sqrt;

	if (_mm_cvtss_f32(msqr) == 0.0f)
		return ((t_vec4s){.simd = _mm_set1_ps(0.f)});
	sqrt = _mm_sqrt_ps(msqr);
	return ((t_vec4s)
		{
			.simd = _mm_div_ps(in.simd, sqrt)
		});
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4s_linear_algebra.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:43:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/19 08:47:27y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

bool	lag_vec4s_eq(const t_vec4s a, const t_vec4s b,
						float tolerance)
{
	const __m128	sign_mask = _mm_set1_ps(-0.0f);
	const __m128	abs_diff = _mm_andnot_ps(\
						sign_mask, \
						_mm_sub_ps(a.simd, b.simd) \
					);
	const __m128	load_tol = _mm_set1_ps(tolerance);
	const __m128	cmp = _mm_cmp_ps(\
						abs_diff, \
						load_tol, \
						_CMP_LT_OQ \
					);
	const int	mask = _mm_movemask_ps(cmp);

	return (mask == 0xF);
}

//bool	lag_vec4s_exacteq(const t_vec4s a, const t_vec4s b)
//{
//	const int	mask = _mm_movemask_ps(\
//					_mm_cmp_ps(a.simd, b.simd, _CMP_LT_OQ) \
//				);

//	return (mask == 0xF);
//}

static inline __m128	_mm_msqr_ps(const __m128 vec)
{
	__m128 mul;
	__m128 shuf;
	__m128 sums;


	mul = _mm_mul_ps(vec, vec);
	shuf = _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1));
	sums = _mm_add_ps(mul, shuf);
	shuf = _mm_movehl_ps(shuf, sums);
	sums = _mm_add_ss(sums, shuf);
	return (_mm_shuffle_ps(sums, sums, _MM_SHUFFLE(0, 0, 0, 0)));
}

void	lag_vec4s_normalize(t_vec4s *target)
{
	const __m128	msqr = _mm_msqr_ps(target->simd);//_mm_dp_ps(target->simd, target->simd, 0xFF);
	__m128	isrt;

	if (_mm_cvtss_f32(msqr) == 0.0f)
	{
		*target = (t_vec4s){0};
		return ;
	}
	isrt = _mm_rsqrt_ps(msqr);
	target->simd = _mm_mul_ps(target->simd, isrt);
}

t_vec4s	lag_vec4s_normalize_ret(const t_vec4s in)
{
	const __m128	msqr = _mm_dp_ps(in.simd, in.simd, 0xFF);
	__m128			isrt;

	if (_mm_cvtss_f32(msqr) == 0.0f)
		return ((t_vec4s){.simd = _mm_set1_ps(0.f)});
	isrt = _mm_rsqrt_ps(msqr);
	return ((t_vec4s)
		{
			.simd = _mm_mul_ps(in.simd, isrt)
		});
}

void	lag_vec4s_normalize_new(t_vec4s *out, const t_vec4s in)
{
	const __m128	msqr = _mm_dp_ps(in.simd, in.simd, 0xFF);
	__m128	isrt;

	if (_mm_cvtss_f32(msqr) == 0.0f)
	{
		*out = (t_vec4s){0};
		return ;
	}
	isrt = _mm_rsqrt_ps(msqr);
	out->simd = _mm_mul_ps(in.simd, isrt);
}

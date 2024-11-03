/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_2_ps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 23:24:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 07:16:36 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

void	lag_vec4s_scaleby(t_vec4s *out, const t_vec4s in,
						float scalar)
{
	out->simd = _mm_mul_ps(in.simd, _mm_set1_ps(scalar));
}

t_vec4s	lag_vec4s_scaleby_ret(const t_vec4s in, float scalar)
{
	return ((t_vec4s)
		{
			.simd = _mm_mul_ps(in.simd, _mm_set1_ps(scalar))
		});
}

void	lag_vec4s_negate_new(t_vec4s *out, const t_vec4s in)
{
	out->simd = _mm_sub_ps(_mm_set1_ps(0.0f), in.simd);
}

void	lag_vec4s_negate(t_vec4s *target)
{
	target->simd = _mm_sub_ps(_mm_set1_ps(0.0f), target->simd);
}

t_vec4s	lag_vec4s_negate_ret(const t_vec4s in)
{
	return ((t_vec4s)
		{
			.simd = _mm_sub_ps(_mm_set1_ps(0.0f), in.simd)
		});
}

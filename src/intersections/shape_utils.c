/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:30:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 13:30:07 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	lag_mat4s_transpose(const t_mat4s *m, t_mat4s *out)
{
	const __m128	tmp0 = _mm_unpacklo_ps(m->r1.simd, m->r2.simd);
	const __m128	tmp1 = _mm_unpacklo_ps(m->r3.simd, m->r4.simd);
	const __m128	tmp2 = _mm_unpackhi_ps(m->r1.simd, m->r2.simd);
	const __m128	tmp3 = _mm_unpackhi_ps(m->r3.simd, m->r4.simd);

	out->r1.simd = _mm_movelh_ps(tmp0, tmp1);
	out->r2.simd = _mm_movehl_ps(tmp1, tmp0);
	out->r3.simd = _mm_movelh_ps(tmp2, tmp3);
	out->r4.simd = _mm_movehl_ps(tmp3, tmp2);
}

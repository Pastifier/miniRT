/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_operations_1_ps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:57:10 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 07:16:26 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lag.h"

void	lag_vec4s_add(t_vec4s *out, const t_vec4s in1,
						const t_vec4s in2)
{
	out->simd = _mm_add_ps(in1.simd, in2.simd);
}

t_vec4s	lag_vec4s_add_ret(const t_vec4s in1, const t_vec4s in2)
{
	return ((t_vec4s)
		{
			.simd = _mm_add_ps(in1.simd, in2.simd)
		});
}

void	lag_vec4s_sub(t_vec4s *out, const t_vec4s in1,
						const t_vec4s in2)
{
	out->simd = _mm_sub_ps(in1.simd, in2.simd);
}

t_vec4s	lag_vec4s_sub_ret(const t_vec4s in1, const t_vec4s in2)
{
	return ((t_vec4s)
		{
			.simd = _mm_sub_ps(in1.simd, in2.simd)
		});
}

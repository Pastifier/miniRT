/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 22:13:08 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 07:14:22 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

t_vec4s	lag_vec4s_ret(float x, float y, float z, float w)
{
	return ((t_vec4s)
		{
			.simd = _mm_set_ps(w, z, y, x)
		});
}

void	lag_vec4sp_init(t_vec4s *target, float x, float y,
						float z)
{
	target->simd = _mm_set_ps(1.0, z, y, x);
}

t_vec4s	lag_vec4sp_ret(float x, float y, float z)
{
	return ((t_vec4s)
		{
			.simd = _mm_set_ps(1.0, z, y, x)
		});
}

void	lag_vec4sv_init(t_vec4s *target, float x, float y,
						float z)
{
	target->simd = _mm_set_ps(0.0, z, y, x);
}

t_vec4s	lag_vec4sv_ret(float x, float y, float z)
{
	return ((t_vec4s)
		{
			.simd = _mm_set_ps(0.0, z, y, x)
		});
}

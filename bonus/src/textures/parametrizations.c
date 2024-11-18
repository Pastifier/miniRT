/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametrizations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:00:42 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 15:46:42 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec2s	rt_get_sphere_uv_local(t_vec4s *hitp)
{
	const float	two_pi = 2.f * (float)M_PI;
	t_vec2s		uv;
	float		phi;
	float		theta;
	t_vec4s		op_hitp;

	op_hitp = *hitp;
	phi = atan2f(hitp->z, hitp->x);
	theta = acosf(hitp->y / lag_vec4s_magnitude_ret(op_hitp));
	if (phi < 0.f)
		phi += two_pi;
	if (theta < 0.f)
		theta += (float)M_PI;
	uv.x = phi / two_pi;
	if (uv.x >= 1.f)
		uv.x = 0.999f;
	uv.y = theta / (float)M_PI;
	if (uv.y >= 1.f)
		uv.y = 0.999f;
	return (uv);
}

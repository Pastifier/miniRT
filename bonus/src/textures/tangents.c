/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tangents.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:16:37 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/17 19:26:08 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec4s rt_get_cylinder_tangent(t_vec4s *local_normal, t_obj *cylinder)
{
	const t_vec4s	j_hat = lag_vec4sv_ret(0, 1, 0);
	t_vec4s			tangent;

	(void)cylinder;
	if (fabsf(local_normal->y) < 0.999f)
	{
		lag_vec4s_cross(&tangent, *local_normal, j_hat);
	}
	else
	{
		tangent = lag_vec4sv_ret(1, 0, 0);
	}
	lag_vec4s_normalize(&tangent);
	return tangent;
}

t_vec4s	rt_get_sphere_tangent(t_vec4s *local_normal)
{
	t_vec4s			reference;
	t_vec4s			retval;

	if (fabsf(lag_vec4s_magnitude_ret(*local_normal)) < 0.999f)
		reference = lag_vec4sv_ret(0, 1, 0);
	else
		reference = lag_vec4sv_ret(1, 0, 0);
	lag_vec4s_cross(&retval, reference, *local_normal);
	lag_vec4s_normalize(&retval);
	return (retval);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:51:45 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/20 09:58:10 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"
#include "libft.h"

static inline t_vec4s	quat_from_axis_angle(const t_vec4s axis, float theta)
{
	t_vec4s		q;
	float		sin_half_theta;

	sin_half_theta = sinf(theta / 2);
	q.w = cosf(theta / 2);
	q.x = axis.x * sin_half_theta;
	q.y = axis.y * sin_half_theta;
	q.z = axis.z * sin_half_theta;
	return (q);
}

static inline t_mat4s	mat4_from_quat(const t_vec4s q)
{
	t_mat4s	ret;
	t_vec4s	x;
	t_vec4s	y;
	t_vec4s	z;
	t_vec4s	w;

	x.x = q.x * q.x;
	y.y = q.y * q.y;
	z.z = q.z * q.z;
	x.y = q.x * q.y;
	x.z = q.x * q.z;
	y.z = q.y * q.z;
	w.x = q.w * q.x;
	w.y = q.w * q.y;
	w.z = q.w * q.z;
	lag_vec4sv_init(&ret.r1, 1 - 2 * (y.y + z.z), 2 * (x.y - w.z), 2
		* (x.z + w.y));
	lag_vec4sv_init(&ret.r2, 2 * (x.y + w.z), 1 - 2 * (x.x + z.z), 2
		* (y.z - w.x));
	lag_vec4sv_init(&ret.r3, 2 * (x.z - w.y), 2 * (y.z + w.x), 1 - 2
		* (x.x + y.y));
	lag_vec4sp_init(&ret.r4, 0.f, 0.f, 0.f);
	return (ret);
}

/// @param u Normalized orientation vector.
/// @warning At the risk of being repetitive, `u` must be a normalized vector!!
t_mat4s	rt_extract_rot_vertical(const t_vec4s u)
{
	t_vec4s	j_hat;
	t_vec4s	rot_axis;
	float	theta;
	t_vec4s	q;

	j_hat = lag_vec4sv_ret(0.f, 1.f, 0.f);
	if (u.x == 0 && fabsf(u.y - 1) < EPSILON && u.z == 0)
		return (lag_mat4s_identity());
	if (u.x == 0 && fabsf(u.y + 1) < EPSILON && u.z == 0)
		return (lag_mat4s_rotation_x((float)-M_PI));
	rot_axis = lag_vec4s_cross_ret(j_hat, u);
	if (lag_vec4s_magnitude_ret(rot_axis) < EPSILON)
		return (lag_mat4s_identity());
	rot_axis = lag_vec4s_normalize_highp(rot_axis);
	theta = acosf(fmaxf(-1.0f, fminf(1.0f, lag_vec4s_dot_ret(&u, &j_hat))));
	q = quat_from_axis_angle(rot_axis, theta);
	return (mat4_from_quat(q));
}

bool	is_normalised(t_vec4s vec, int curr_line)
{
	float	mag;

	lag_vec4s_magnitude(&mag, vec);
	if (fabsf(mag - 1.0f) > EPSILON)
	{
		ft_fprintf(2, "Warning on line %d: orientation vector not normalised. \
		\n\tWe'll normalise it for you.\n", curr_line);
		return (false);
	}
	return (true);
}

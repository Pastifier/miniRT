/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:51:45 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/04 13:52:26 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lag.h"

static inline t_vec4s quat_from_axis_angle(const t_vec4s axis, float theta)
{
	t_vec4s		q;
	const float	sin_half_theta = sinf(theta / 2);

	q.w = cosf(theta / 2);
	q.x = axis.x * sin_half_theta;
	q.y = axis.y * sin_half_theta;
	q.z = axis.z * sin_half_theta;
	return (q);
}

static inline t_mat4s	mat4_from_quat(const t_vec4s q)
{
	t_mat4s	ret;
	float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
	float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
	float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

	lag_vec4sv_init(&ret.r1, 1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy));
	lag_vec4sv_init(&ret.r2, 2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx));
	lag_vec4sv_init(&ret.r3, 2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy));
	lag_vec4sp_init(&ret.r4, 0.f, 0.f, 0.f);
	return (ret);
}

/// @param u Normalized orientation vector.
/// @warning At the risk of being repetitive, `u` must be a normalized vector!!
t_mat4s rt_extract_rot_vertical(const t_vec4s u)
{
	const t_vec4s	j_hat = lag_vec4sv_ret(0.f, 1.f, 0.f);
	t_vec4s			rot_axis;
	float			theta;
	t_vec4s			q;

	if (u.x == 0 && fabsf(u.y - 1) < EPSILON && u.z == 0)
		return lag_mat4s_identity();
	if (u.x == 0 && fabsf(u.y + 1) < EPSILON && u.z == 0)
		return lag_mat4s_rotation_x((float)-M_PI);

	rot_axis = lag_vec4s_cross_ret(j_hat, u);
	if (lag_vec4s_magnitude_ret(rot_axis) < EPSILON)
		return lag_mat4s_identity();
	rot_axis = lag_vec4s_normalize_highp(rot_axis);

	theta = acosf(fmaxf(-1.0f, fminf(1.0f, lag_vec4s_dot_ret(&u, &j_hat))));
	q = quat_from_axis_angle(rot_axis, theta);
	return (mat4_from_quat(q));
}

bool	is_normalised(t_vec4s vec)
{
	float	mag;

	lag_vec4s_magnitude(&mag, vec);
	if (fabsf(mag - 1.0f) > EPSILON)
		return (false);
	return (true);
}

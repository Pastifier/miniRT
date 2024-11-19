/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:38:22 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/19 17:18:51 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_mat4s rotation_matrix_from_axis_angle(const t_vec4s *axis, float angle)
{
	t_mat4s rot;
	float cos_theta = cosf(angle);
	float sin_theta = sinf(angle);
	float one_minus_cos = 1.0f - cos_theta;

	// Ensure the axis is normalized
	t_vec4s k = *axis;
	lag_vec4s_normalize(&k);

	// Components for readability
	float kx = k.x, ky = k.y, kz = k.z;
	float kx2 = kx * kx, ky2 = ky * ky, kz2 = kz * kz;
	float kxy = kx * ky, kxz = kx * kz, kyz = ky * kz;

	// Rotation matrix based on Rodrigues' rotation formula
	rot.r1 = lag_vec4s_ret(
		cos_theta + kx2 * one_minus_cos,
		kxy * one_minus_cos - kz * sin_theta,
		kxz * one_minus_cos + ky * sin_theta,
		0.0f);

	rot.r2 = lag_vec4s_ret(
		kxy * one_minus_cos + kz * sin_theta,
		cos_theta + ky2 * one_minus_cos,
		kyz * one_minus_cos - kx * sin_theta,
		0.0f);

	rot.r3 = lag_vec4s_ret(
		kxz * one_minus_cos - ky * sin_theta,
		kyz * one_minus_cos + kx * sin_theta,
		cos_theta + kz2 * one_minus_cos,
		0.0f);

	// Set last row for homogenous coordinates (no translation)
	rot.r4 = lag_vec4s_ret(0.0f, 0.0f, 0.0f, 1.0f);

	return rot;
}

static inline void	update_camera_state(t_camera *camera)
{
	lag_vec4s_normalize(&camera->up);
	lag_vec4s_normalize(&camera->left);
	lag_vec4s_normalize(&camera->forward);
	camera->inv_transform = lag_mat4s_rows_ret(
		lag_vec4s_ret(camera->left.x, camera->left.y, camera->left.z, 0.0f),
		lag_vec4s_ret(camera->up.x, camera->up.y, camera->up.z, 0.0f),
		lag_vec4s_ret(-camera->forward.x, -camera->forward.y, -camera->forward.z, 0.0f),
		lag_vec4s_ret(0.0f, 0.0f, 0.0f, 1.0f)
	);
	lag_mat4s_cross_mat4s(camera->inv_transform, \
		lag_mat4s_translation(-camera->trans.x, -camera->trans.y, -camera->trans.z), \
		&camera->inv_transform);
	camera->inv_transform = rt_get_cam_inverse(&camera->inv_transform);
}

void	camera_rotations(t_program *state)
{
	const t_vec4s	j_hat = lag_vec4sv_ret(0.f, 1.f, 0.f);
	t_mat4s	rot;

	if (state->movement.left == true)
	{
		rot = rotation_matrix_from_axis_angle(&j_hat, -(PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
		lag_mat4s_cross_vec4s(&rot, &state->cam.left, &state->cam.left);
		lag_mat4s_cross_vec4s(&rot, &state->cam.up, &state->cam.up);
	}
	if (state->movement.right == true)
	{
		rot = rotation_matrix_from_axis_angle(&j_hat, (PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
		lag_mat4s_cross_vec4s(&rot, &state->cam.left, &state->cam.left);
		lag_mat4s_cross_vec4s(&rot, &state->cam.up, &state->cam.up);
	}
	if (state->movement.up == true)
	{
		rot = rotation_matrix_from_axis_angle(&state->cam.left, (YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
		lag_mat4s_cross_vec4s(&rot, &state->cam.left, &state->cam.left);
		lag_mat4s_cross_vec4s(&rot, &state->cam.up, &state->cam.up);
	}
	if (state->movement.down == true)
	{
		rot = rotation_matrix_from_axis_angle(&state->cam.left, -(YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
		lag_mat4s_cross_vec4s(&rot, &state->cam.left, &state->cam.left);
		lag_mat4s_cross_vec4s(&rot, &state->cam.up, &state->cam.up);
	}
	update_camera_state(&state->cam);
}
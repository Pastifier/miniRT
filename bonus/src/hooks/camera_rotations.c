/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:38:22 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/19 20:04:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

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

static inline void	_rotcam_apply_pitch_rot(t_program *state, bool left)
{
	const float	angle = (PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4s		rot;

	if (left)
		rot = lag_mat4s_rotation_y(-angle);
	else
		rot = lag_mat4s_rotation_y(angle);
	lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	lag_mat4s_cross_vec4s(&rot, &state->cam.left, &state->cam.left);
	lag_mat4s_cross_vec4s(&rot, &state->cam.up, &state->cam.up);
}

static inline void	_rotcam_apply_yaw_rot(t_program *state, bool up)
{
	const float	angle = (YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time;
	t_mat4s		rot;

	if (up)
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, angle);
	else
		rot = rt_rotation_matrix_from_axis_angle(&state->cam.left, -angle);
	lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	lag_mat4s_cross_vec4s(&rot, &state->cam.left, &state->cam.left);
	lag_mat4s_cross_vec4s(&rot, &state->cam.up, &state->cam.up);
}

void	camera_rotations(t_program *state)
{
	bool	state_changed;

	if (state->movement.left == true)
	{
		_rotcam_apply_pitch_rot(state, true);
		state_changed = true;
	}
	if (state->movement.right == true)
	{
		_rotcam_apply_pitch_rot(state, false);
		state_changed = true;
	}
	if (state->movement.up == true)
	{
		_rotcam_apply_yaw_rot(state, true);
		state_changed = true;
	}
	if (state->movement.down == true)
	{
		_rotcam_apply_yaw_rot(state, false);
		state_changed = true;
	}
	if (state_changed)
		update_camera_state(&state->cam);
}

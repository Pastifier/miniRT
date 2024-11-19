/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:18:05 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/19 17:36:13 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static inline void	update_camera_state(t_camera *camera)
{
	lag_vec4s_normalize(&camera->up);
	lag_vec4s_normalize(&camera->left);
	lag_vec4s_normalize(&camera->forward);
	camera->inv_transform = lag_mat4s_rows_ret(\
		lag_vec4s_ret(camera->left.x, camera->left.y, camera->left.z, 0.0f), \
		lag_vec4s_ret(camera->up.x, camera->up.y, camera->up.z, 0.0f), \
		lag_vec4s_ret(-camera->forward.x, -camera->forward.y, \
			-camera->forward.z, 0.0f), \
		lag_vec4s_ret(0.0f, 0.0f, 0.0f, 1.0f) \
	);
	lag_mat4s_cross_mat4s(camera->inv_transform, \
		lag_mat4s_translation(\
			-camera->trans.x, -camera->trans.y, -camera->trans.z \
		), \
			&camera->inv_transform \
		);
	camera->inv_transform = rt_get_cam_inverse(&camera->inv_transform);
}

static inline void	_movecam_sideways_check(t_program *state,
						bool *state_changed)
{
	t_vec4s	scaled_left;

	lag_vec4s_scaleby(&scaled_left, state->cam.left, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->movement.a)
	{
		lag_vec4s_add(&state->cam.trans, &scaled_left, &state->cam.trans);
		*state_changed = true;
	}
	if (state->movement.d)
	{
		lag_vec4s_sub(&state->cam.trans, &state->cam.trans, &scaled_left);
		*state_changed = true;
	}
}

static inline void	_movecam_longitudinally_check(t_program *state,
						bool *state_changed)
{
	t_vec4s	scaled_forward;

	lag_vec4s_scaleby(&scaled_forward, state->cam.forward, \
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->movement.w)
	{
		lag_vec4s_add(&state->cam.trans, &scaled_forward, &state->cam.trans);
		*state_changed = true;
	}
	if (state->movement.s)
	{
		lag_vec4s_sub(&state->cam.trans, &state->cam.trans, &scaled_forward);
		*state_changed = true;
	}
}

static inline void	_movecam_elevation_check(t_program *state,
						bool *state_changed)
{
	if (state->movement.space)
	{
		state->cam.trans.y += (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
	if (state->movement.lshift)
	{
		state->cam.trans.y -= (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
}

void	camera_controls(t_program *state)
{
	bool	state_changed;

	state_changed = false;
	if (state->movement.a || state->movement.d || state->movement.s
		|| state->movement.w || state->movement.space || state->movement.lshift)
	{
		_movecam_sideways_check(state, &state_changed);
		_movecam_longitudinally_check(state, &state_changed);
		_movecam_elevation_check(state, &state_changed);
		if (state_changed)
			update_camera_state(&state->cam);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:22:17 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/07 02:38:20ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "keys.h"
#include "macros.h"

#define MOVE_SPEED 5.f
#define PITCH_SPEED 0.3f
#define YAW_SPEED 0.3f

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
	if (camera->forward.x < EPSILON && camera->forward.z < EPSILON)
		camera->left = lag_vec4s_ret(-1.0f, 0.0f, 0.0f, 0.0f);
	else
		camera->left = lag_vec4s_cross_ret(camera->forward, lag_vec4s_ret(0.0f, 1.0f, 0.0f, 0.0f));
	lag_vec4s_normalize(&camera->left);
	camera->up = lag_vec4s_cross_ret(camera->left, camera->forward);
	lag_vec4s_normalize(&camera->up);
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

static inline void	update_object_cache(t_obj *object)
{
	object->inv_transform = lag_mat4s_get_transform_inverse(\
		object->rot, \
		object->scale.simd, \
		object->trans.simd
	);
	lag_mat4s_transpose(&object->inv_transform, &object->transposed_inverse);
}

// Function to handle camera movement controls
void	camera_controls(t_program *state)
{
	t_vec4s	scaled_forward, scaled_left;

	lag_vec4s_scaleby(&scaled_forward, state->cam.forward, (MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	lag_vec4s_scaleby(&scaled_left, state->cam.left, (MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);

	if (state->movement.a)
		lag_vec4s_add(&state->cam.trans, &scaled_left, &state->cam.trans);
	if (state->movement.d)
		lag_vec4s_sub(&state->cam.trans, &state->cam.trans, &scaled_left);
	if (state->movement.w)
		lag_vec4s_add(&state->cam.trans, &scaled_forward, &state->cam.trans);
	if (state->movement.s)
		lag_vec4s_sub(&state->cam.trans, &state->cam.trans, &scaled_forward);
	if (state->movement.space)
		state->cam.trans.y += (MOVE_SPEED * state->delta_time);
	if (state->movement.lctrl)
		state->cam.trans.y -= (MOVE_SPEED * state->delta_time);
	update_camera_state(&state->cam);
}

void	camera_rotations(t_program *state)
{
	t_mat4s	rot;

	if (state->movement.left == true)
	{
		rot = rotation_matrix_from_axis_angle(&state->cam.up, -(PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	}
	if (state->movement.right == true)
	{
		rot = rotation_matrix_from_axis_angle(&state->cam.up, (PITCH_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	}
	if (state->movement.up == true)
	{
		rot = rotation_matrix_from_axis_angle(&state->cam.left, (YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	}
	if (state->movement.down == true)
	{
		rot = rotation_matrix_from_axis_angle(&state->cam.left, -(YAW_SPEED + MOVE_SPEED / 10.f) * state->delta_time);
		lag_mat4s_cross_vec4s(&rot, &state->cam.forward, &state->cam.forward);
	}
	lag_vec4s_normalize(&state->cam.forward);
	update_camera_state(&state->cam);
}

// Function to handle object movement controls
void	object_controls(t_program *state)
{
	t_obj	*selected_object = state->selected.object;
	t_vec4s	scaled_forward, scaled_left;
	t_vec4s op = lag_vec4s_ret(selected_object->trans.x, state->cam.trans.y, selected_object->trans.z, 1);
	t_vec4s	viewport_forward;
	lag_vec4s_sub(&viewport_forward, &op, &state->cam.trans);
	lag_vec4s_normalize(&viewport_forward);

	lag_vec4s_scaleby(&scaled_forward, viewport_forward, (MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	lag_vec4s_scaleby(&scaled_left, state->cam.left, (MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);

	if (state->movement.a)
		lag_vec4s_add(&selected_object->trans, &selected_object->trans, &scaled_left);
	if (state->movement.d)
		lag_vec4s_sub(&selected_object->trans, &selected_object->trans, &scaled_left);
	if (state->movement.w)
		lag_vec4s_add(&selected_object->trans, &scaled_forward, &selected_object->trans);
	if (state->movement.s)
		lag_vec4s_sub(&selected_object->trans, &selected_object->trans, &scaled_forward);
	if (state->movement.space)
		selected_object->trans.y += (MOVE_SPEED * state->delta_time);
	if (state->movement.lctrl)
		selected_object->trans.y -= (MOVE_SPEED * state->delta_time);
	update_object_cache(selected_object);
}

int	check_state(void *context)
{
	t_program	*state = (t_program *)context;
	bool		state_changed = false;

	if (state->stop)
	{
		if (!state->selected.is_cam)
		{
			state->selected.is_cam = true;
			state->selected.object = NULL;
			state->stop = false;
		}
		else
			return (destroy_program(context), 0);
	}
	if (state->selected.is_cam)
	{
		camera_controls(state);
		camera_rotations(state);
		state_changed = true;
	}
	else
	{
		object_controls(state);
		state_changed = true;
	}
	if (state_changed)
		update(context);
	return (0);
}


int	check_key_presses(int keysym, void *context)
{
	t_program	*state;

	state = (t_program *)context;
	if (keysym == KEY_ESC)
		return (state->stop = true, 0);
	if (keysym == KEY_A)
		state->movement.a = true;
	if (keysym == KEY_D)
		state->movement.d = true;
	if (keysym == KEY_S)
		state->movement.s = true;
	if (keysym == KEY_W)
		state->movement.w = true;
	if (keysym == KEY_SPACE)
		state->movement.space = true;
	if (keysym == KEY_LCTRL)
		state->movement.lctrl = true;
	if (keysym == AKEY_U)
		state->movement.up = true;
	if (keysym == AKEY_D)
		state->movement.down = true;
	if (keysym == AKEY_L)
		state->movement.left = true;
	if (keysym == AKEY_R)
		state->movement.right = true;
	return (keysym);
}

int	check_key_releases(int keysym, void *param)
{
	t_program	*state = (t_program *)param;

	if (keysym == KEY_A)
		state->movement.a = false;
	if (keysym == KEY_D)
		state->movement.d = false;
	if (keysym == KEY_S)
		state->movement.s = false;
	if (keysym == KEY_W)
		state->movement.w = false;
	if (keysym == KEY_SPACE)
		state->movement.space = false;
	if (keysym == KEY_LCTRL)
		state->movement.lctrl = false;
	if (keysym == AKEY_U)
		state->movement.up = false;
	if (keysym == AKEY_D)
		state->movement.down = false;
	if (keysym == AKEY_L)
		state->movement.left = false;
	if (keysym == AKEY_R)
		state->movement.right = false;
	return (keysym);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:22:17 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/06 17:03:32 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "keys.h"
#include "macros.h"

#define MOVE_SPEED 0.4f
#define PITCH_SPEED 0.08f
#define YAW_SPEED 0.06f

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

int	check_state(void *context)
{
	t_program	*state;
	bool		state_changed;

	state = (t_program *)context;
	state_changed = false; // make it so everything only gets updated when it needs to be. Including in the camera update function.
	if (state->stop == true)
		destroy_program(context);
	if (state->movement.a == true)
	{
		state->cam.trans.x -= MOVE_SPEED;
		state_changed = true;
	}
	if (state->movement.d == true)
	{
		state->cam.trans.x += MOVE_SPEED;
		state_changed = true;
	}
	if (state->movement.w == true)
	{
		lag_vec4s_add(&state->cam.trans, &state->cam.forward, &state->cam.trans);
		state_changed = true;
	}
	if (state->movement.s == true)
	{
		lag_vec4s_sub(&state->cam.trans, &state->cam.trans, &state->cam.forward);
		state_changed = true;
	}
	if (state->movement.space == true)
	{
		state->cam.trans.y += MOVE_SPEED;
		state_changed = true;
	}
	if (state->movement.lctrl == true)
	{
		state->cam.trans.y -= MOVE_SPEED;
		state_changed = true;
	}
	if (state_changed)
		update_camera_state(&state->cam);
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
	printf("Keysym: %d\n", keysym);
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
	return (keysym);
}
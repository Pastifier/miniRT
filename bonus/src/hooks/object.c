/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:18:38 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/19 15:11:22 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static inline void	update_object_cache(t_obj *object)
{
	object->inv_transform = lag_mat4s_get_transform_inverse(\
		object->rot, \
		object->scale.simd, \
		object->trans.simd \
	);
	lag_mat4s_transpose(&object->inv_transform, &object->transposed_inverse);
}

static inline void	_move_sideways_check(t_program *state, bool *state_changed)
{
	t_obj	*selected_object;
	t_vec4s	scaled_left;

	lag_vec4s_scaleby(&scaled_left, state->cam.left,
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	selected_object = state->selected.object;
	if (state->movement.a)
	{
		lag_vec4s_add(&selected_object->trans, &selected_object->trans,
			&scaled_left);
		*state_changed = true;
	}
	if (state->movement.d)
	{
		lag_vec4s_sub(&selected_object->trans, &selected_object->trans,
			&scaled_left);
		*state_changed = true;
	}
}

static inline void	_move_longitudinally_check(t_program *state,
						bool *state_changed)
{
	t_obj	*selected_object;
	t_vec4s	viewport_forward;
	t_vec4s	op;

	selected_object = state->selected.object;
	op = lag_vec4s_ret(selected_object->trans.x, \
		state->cam.trans.y, selected_object->trans.z, 1);
	lag_vec4s_sub(&viewport_forward, &op, &state->cam.trans);
	viewport_forward.w = 0.f;
	lag_vec4s_normalize(&viewport_forward);
	lag_vec4s_scaleby(&viewport_forward, viewport_forward,
		(MOVE_SPEED + (MOVE_SPEED / 2.f)) * state->delta_time);
	if (state->movement.w)
	{
		lag_vec4s_add(&selected_object->trans, &selected_object->trans,
			&viewport_forward);
		*state_changed = true;
	}
	if (state->movement.s)
	{
		lag_vec4s_sub(&selected_object->trans, &selected_object->trans,
			&viewport_forward);
		*state_changed = true;
	}
}

static inline void	_move_elevation_check(t_program *state, bool *state_changed)
{
	t_obj	*selected_object;

	selected_object = state->selected.object;
	if (state->movement.space)
	{
		selected_object->trans.y += (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
	if (state->movement.lshift)
	{
		selected_object->trans.y -= (MOVE_SPEED * state->delta_time);
		*state_changed = true;
	}
}

void	object_controls(t_program *state)
{
	t_obj	*selected_object;
	bool	state_changed;

	state_changed = false;
	selected_object = state->selected.object;
	_move_sideways_check(state, &state_changed);
	_move_longitudinally_check(state, &state_changed);
	_move_elevation_check(state, &state_changed);
	if (state_changed)
		update_object_cache(selected_object);
}

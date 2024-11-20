/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:11:55 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/19 20:20:15 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "keys.h"
#include "macros.h"

int	check_state(void *context)
{
	t_program	*state;

	state = (t_program *)context;
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
		if (state->movement.left || state->movement.right
			|| state->movement.up || state->movement.down)
			camera_rotations(state);
	}
	else if (state->movement.a || state->movement.d || state->movement.s
		|| state->movement.w || state->movement.space || state->movement.lshift)
		object_controls(state);
	return (update(context), 0);
}

static inline void	_check_movement_controls(t_program *state, int keysym)
{
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
	if (keysym == KEY_LSHIFT)
		state->movement.lshift = true;
	if (keysym == AKEY_U)
		state->movement.up = true;
	if (keysym == AKEY_D)
		state->movement.down = true;
	if (keysym == AKEY_L)
		state->movement.left = true;
	if (keysym == AKEY_R)
		state->movement.right = true;
}

static inline void	_check_config_controls(t_program *state, int keysym)
{
	if (keysym == KEY_R)
		state->world.refract_reflect ^= true;
}

int	check_key_presses(int keysym, void *context)
{
	t_program	*state;

	state = (t_program *)context;
	if (keysym == KEY_ESC)
	{
		state->stop = true;
		return (0);
	}
	_check_config_controls(state, keysym);
	_check_movement_controls(state, keysym);
	return (keysym);
}

int	check_key_releases(int keysym, void *param)
{
	t_program	*state;

	state = (t_program *)param;
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
	if (keysym == KEY_LSHIFT)
		state->movement.lshift = false;
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

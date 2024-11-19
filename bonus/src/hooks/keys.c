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

int	check_state(void *context)
{
	t_program	*state = (t_program *)context;

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
	if (keysym == KEY_R)
		state->world.refract_reflect ^= true;
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

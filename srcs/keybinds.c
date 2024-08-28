/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:52:08 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 15:13:02 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "keys.h"
#include "camera.h"
#include <stdio.h>

int	move_camera(int keycode, t_program *context)
{
	double		move_speed;
	t_vector3	move;
	t_camera	*camera;

	camera = &context->camera;
	move_speed = 0.5;
	printf("checking for camera movement\n");
	if (keycode == KEY_W)
		move = (t_vector3){0.0, 0.0, move_speed};
	else if (keycode == KEY_S)
		move = (t_vector3){0.0, 0.0, -move_speed};
	else if (keycode == KEY_A)
		move = (t_vector3){-move_speed, 0.0, 0.0};
	else if (keycode == KEY_D)
		move = (t_vector3){move_speed, 0.0, 0.0};
	else if (keycode == KEY_Q)
		move = (t_vector3){0.0, -move_speed, 0.0};
	else if (keycode == KEY_E)
		move = (t_vector3){0.0, move_speed, 0.0};
	else
		return (0);
	printf("Moving camera\n");
	camera->center = vec3_add(camera->center, move);
	render(context);
	return (1);
}

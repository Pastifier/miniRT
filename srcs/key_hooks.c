/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/15 02:19:31 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "macros.h"
#include "linear_algebra.h"
#include "keys.h"
#include <stdio.h>
#include "mlx.h"

//static void	move_camera(int keycode, t_program *context)
//{
//	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
//		|| keycode == KEY_D || keycode == KEY_UP || keycode == KEY_DOWN
//		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
//	{
//		refresh_camera(keycode, &context->camera);
//		mlx_clear_window(context->mlx, context->win);
//		render_new_frame(context);
//	}
//}
void	rotate_yaw(t_camera *cam, double angle)
{
	t_mat4x4 rotation = rotation_y(angle);
	cam->look_at = mat4x4_cross_vec(&rotation, &cam->look_at);
	cam->right = mat4x4_cross_vec(&rotation, &cam->right);
	vnormalize(&cam->look_at);
	vnormalize(&cam->right);
}

void	rotate_pitch(t_camera *cam, double angle)
{
	t_mat4x4 rotation = rotation_x(angle);
	cam->look_at = mat4x4_cross_vec(&rotation, &cam->look_at);
	cam->up = mat4x4_cross_vec(&rotation, &cam->up);
	vnormalize(&cam->look_at);
	vnormalize(&cam->up);
}

void	move_camera(int keycode, t_camera *cam)
{
	double	move_speed = 0.2;
	double	rotate_speed = M_PI / 180.0 * 5;
	t_double4	scaled_look_at;
	t_double4	neg_scaled_look_at;

	d4mul(&scaled_look_at, &cam->look_at, move_speed);
	neg_scaled_look_at = scaled_look_at;
	d4negate(&neg_scaled_look_at);
	// Vectors are fucked.
	if (keycode == KEY_W)
		d4add(&cam->position, &cam->position, &scaled_look_at);
	else if (keycode == KEY_S)
		d4add(&cam->position, &cam->position, &neg_scaled_look_at);
	else if (keycode == KEY_A)
		d4add(&cam->position, &cam->position, &scaled_look_at);
	else if (keycode == KEY_D)
		d4add(&cam->position, &cam->position, &neg_scaled_look_at);
	else if (keycode == KEY_LEFT)
		rotate_yaw(cam, -rotate_speed);
	else if (keycode == KEY_RIGHT)
		rotate_yaw(cam, rotate_speed);
	else if (keycode == KEY_UP)
		rotate_pitch(cam, -rotate_speed);
	else if (keycode == KEY_DOWN)
		rotate_pitch(cam, rotate_speed);

	cam->transform = view_transform(cam->position, cam->look_at, cam->up);
	cam->inverse = mat4x4_inverse(&cam->transform);
}


int	key_hook(int keycode, t_program *context)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(context->mlx, context->win);
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A
		|| keycode == KEY_D || keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
	{
		move_camera(keycode, &context->camera);
		mlx_clear_window(context->mlx, context->win);
		render_new_frame(context);
	}
	return (0);
}

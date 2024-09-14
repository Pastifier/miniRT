/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:35:45 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/15 02:10:49 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rtmath.h"
#include "objects.h"
#include "macros.h"
#include "keys.h"
#include "linear_algebra.h"

void	setup_camera(t_camera *camera, double fov)
{
	camera->hsize = WIN_WIDTH;
	camera->vsize = WIN_HEIGHT;
	camera->field_of_view = fov;
	camera->half_view = tan(camera->field_of_view / 2);
	camera->aspect_ratio = (double)camera->hsize / (double)camera->vsize;
	if (camera->aspect_ratio >= 1)
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / camera->aspect_ratio;
	}
	else
	{
		camera->half_width = camera->half_view * camera->aspect_ratio;
		camera->half_height = camera->half_view;
	}
	camera->pixel_size = (double)(camera->half_width * 2) / (double)camera->hsize;
	point(&camera->position, 0, 1.5, -5);
	vector(&camera->look_at, 0, 0, 1);
	vector(&camera->up, 0, 1, 0);
	d4_cross_vec(&camera->right, &camera->look_at, &camera->up);
	camera->transform = view_transform(camera->position, camera->look_at, camera->up);
	camera->inverse = mat4x4_inverse(&camera->transform);
}

//void	setup_camera(t_camera *camera, double fov)
//{
//	camera->hsize = WIN_WIDTH;
//	camera->vsize = WIN_HEIGHT;
//	camera->field_of_view = fov;
//	camera->half_view = tan(camera->field_of_view / 2);
//	camera->aspect_ratio = (double)camera->hsize / (double)camera->vsize;
//	camera->transform = mat4x4_identity();
//	if (camera->aspect_ratio >= 1)
//	{
//		camera->half_width = camera->half_view;
//		camera->half_height = camera->half_view / camera->aspect_ratio;
//	}
//	else
//	{
//		camera->half_width = camera->half_view * camera->aspect_ratio;
//		camera->half_height = camera->half_view;
//	}
//	camera->pixel_size = (double)(camera->half_width * 2) / (double)camera->hsize;
//}

t_mat4x4	view_transform(t_double4 position, t_double4 look_at, t_double4 up)
{
	t_mat4x4 orientation_matrix;
	t_mat4x4 translation_matrix;
	t_double4 right;

	vnormalize(&look_at);
	d4_cross_vec(&right, &look_at, &up);
	vnormalize(&right);
	d4_cross_vec(&up, &right, &look_at);
	orientation_matrix = mat4x4_identity();
	orientation_matrix.r1 = row4(right.x, right.y, right.z, 0);
	orientation_matrix.r2 = row4(up.x, up.y, up.z, 0);
	orientation_matrix.r3 = row4(-look_at.x, -look_at.y, -look_at.z, 0);
	point(&orientation_matrix.r4, 0, 0, 0);
	translation_matrix = translation(-position.x, -position.y, -position.z);
	return (mat4x4_cross(&orientation_matrix, &translation_matrix));
}

//t_mat4x4	view_transform(t_double4 from, t_double4 to, t_double4 up)
//{
//	t_double4	forward;
//	t_double4	left;
//	t_double4	true_up;
//	t_mat4x4	orientation_matrix;
//	t_mat4x4	translation_matrix;

//	d4sub(&forward, &to, &from);
//	vnormalize(&forward);
//	vnormalize(&up);
//	d4_cross_vec(&left, &forward, &up);
//	d4_cross_vec(&true_up, &left, &forward);
//	orientation_matrix = mat4x4_identity();
//	orientation_matrix.r1 = row4(left.x, left.y, left.z, 0);
//	orientation_matrix.r2 = row4(true_up.x, true_up.y, true_up.z, 0);
//	orientation_matrix.r3 = row4(-forward.x, -forward.y, -forward.z, 0);
//	point(&orientation_matrix.r4, 0, 0, 0);
//	translation_matrix = translation(-from.x, -from.y, -from.z);
//	return (mat4x4_cross(&orientation_matrix, &translation_matrix));
//}

void	refresh_camera(int keycode, t_camera *cam)
{
	t_double4 forward;
	d4sub(&forward, &cam->to, &cam->from);
	vnormalize(&forward);

	t_double4 right;
	d4_cross_vec(&right, &forward, &cam->up);
	vnormalize(&right);

	double move_speed = 0.2;
	double rotation_speed = 0.2;

	if (keycode == KEY_W)
	{
		cam->from.x += forward.x * move_speed;
		cam->from.y += forward.y * move_speed;
		cam->from.z += forward.z * move_speed;

		cam->to.x += forward.x * move_speed;
		cam->to.y += forward.y * move_speed;
		cam->to.z += forward.z * move_speed;
	}
	else if (keycode == KEY_S)
	{
		cam->from.x -= forward.x * move_speed;
		cam->from.y -= forward.y * move_speed;
		cam->from.z -= forward.z * move_speed;

		cam->to.x -= forward.x * move_speed;
		cam->to.y -= forward.y * move_speed;
		cam->to.z -= forward.z * move_speed;
	}
	else if (keycode == KEY_D)
	{
		cam->from.x -= right.x * move_speed;
		cam->from.y -= right.y * move_speed;
		cam->from.z -= right.z * move_speed;

		cam->to.x -= right.x * move_speed;
		cam->to.y -= right.y * move_speed;
		cam->to.z -= right.z * move_speed;
	}
	else if (keycode == KEY_A)
	{
		cam->from.x += right.x * move_speed;
		cam->from.y += right.y * move_speed;
		cam->from.z += right.z * move_speed;

		cam->to.x += right.x * move_speed;
		cam->to.y += right.y * move_speed;
		cam->to.z += right.z * move_speed;
	}
	else if (keycode == KEY_UP)
	{
		cam->to.y += rotation_speed;
	}
	else if (keycode == KEY_DOWN)
	{
		cam->to.y -= rotation_speed;
	}
	else if (keycode == KEY_LEFT)
	{
		cam->to.x -= rotation_speed * 1.5;
	}
	else if (keycode == KEY_RIGHT)
	{
		cam->to.x += rotation_speed * 1.5;
	}

	cam->transform = view_transform(cam->from, cam->to, cam->up);
	cam->inverse = mat4x4_inverse(&cam->transform);
}




t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	t_ray		r;
	t_double4	pixel;
	t_double4	origin;
	t_double4	direction;

	point(&pixel, (camera->half_width - (px + 0.5) * camera->pixel_size),
			(camera->half_height - (py + 0.5) * camera->pixel_size), -1);
	pixel = mat4x4_cross_vec(&camera->inverse, &pixel);
	point(&origin, 0, 0, 0);
	origin = mat4x4_cross_vec(&camera->inverse, &origin);
	d4sub(&direction, &pixel, &origin);
	vnormalize(&direction);
	ray_create(&r, &origin, &direction);
	return (r);
}

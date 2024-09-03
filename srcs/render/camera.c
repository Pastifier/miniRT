/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:35:45 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/03 16:00:32 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rtmath.h"
#include "objects.h"
#include "macros.h"

void	setup_camera(t_camera *camera, double fov)
{
	camera->hsize = WIN_WIDTH;
	camera->vsize = WIN_HEIGHT;
	camera->field_of_view = fov;
	camera->half_view = tan(camera->field_of_view / 2);
	camera->aspect_ratio = (double)camera->hsize / (double)camera->vsize;
	camera->transform = mat4x4_identity();
	if (camera->aspect_ratio > 1)
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / camera->aspect_ratio;
	}
	else
	{
		camera->half_width = camera->half_view * camera->aspect_ratio;
		camera->half_height = camera->half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}

t_mat4x4	view_transform(t_double4 from, t_double4 to, t_double4 up)
{
	t_double4	forward;
	t_double4	left;
	t_double4	true_up;
	t_double4	normal_up;
	t_mat4x4	orientation_matrix;
	t_mat4x4	translation_matrix;

	d4sub(&forward, &to, &from);
	vnormalize(&forward);
	vnorm(&normal_up, &up);
	d4_cross_vec(&left, &forward, &normal_up);
	d4_cross_vec(&true_up, &left, &forward);
	orientation_matrix = mat4x4_identity();
	orientation_matrix.m[0][0] = left.x;
	orientation_matrix.m[0][1] = left.y;
	orientation_matrix.m[0][2] = left.z;
	orientation_matrix.m[1][0] = true_up.x;
	orientation_matrix.m[1][1] = true_up.y;
	orientation_matrix.m[1][2] = true_up.z;
	orientation_matrix.m[2][0] = -forward.x;
	orientation_matrix.m[2][1] = -forward.y;
	orientation_matrix.m[2][2] = -forward.z;
	translation_matrix = translation(-from.x, -from.y, -from.z);
	return (mat4x4_cross(&orientation_matrix, &translation_matrix));
}

t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	t_ray		r;
	t_double4	pixel;
	t_double4	origin;
	t_double4	direction;
	t_mat4x4	inverse_transform;

	point(&pixel, (camera->half_width - (px + 0.5) * camera->pixel_size),
			(camera->half_height - (py + 0.5) * camera->pixel_size), -1);
	pixel = mat4x4_cross_vec(&camera->transform, &pixel);
	point(&origin, 0, 0, 0);
	inverse_transform = mat4x4_inverse(&camera->transform);
	origin = mat4x4_cross_vec(&inverse_transform, &origin);
	d4sub(&direction, &pixel, &origin);
	vnormalize(&direction);
	ray_create(&r, &origin, &direction);
	return (r);
}

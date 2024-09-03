/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:49:26 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 21:11:47binjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "linear_algebra.h"

t_webcam	init_camera(int hsize, int vsize, double fov)
{
	t_webcam	ret;

	ret.hsize = hsize;
	ret.vsize = vsize;
	ret.fov = fov;
	ret.transform = mat4x4_identity();
	ret.half_view = tan(ret.fov / 2.0);
	// remember to catch floating-point exceptions!!!
	ret.aspect = (double)hsize / (double)vsize;
	if (ret.aspect >= 1)
	{
		ret.half_width = ret.half_view;
		ret.half_height = ret.half_view / ret.aspect;
	}
	else
	{
		ret.half_width = ret.half_view * ret.aspect;
		ret.half_height = ret.half_view;
	}
	ret.pixel_size = (ret.half_width * 2) / (double)hsize;
	return (ret);
}

t_ray	to_the_pixel_and_beyond(t_webcam *cam, int px, int py)
{
	t_double2	offsets;
	t_double4	world_coord;
	t_double4	pixel;
	t_double4	origin;
	t_double4	direction;
	t_mat4x4	inv;

	offsets.x = (px * cam->pixel_size) + (0.5 * cam->pixel_size);
	offsets.y = (py * cam->pixel_size) + (0.5 * cam->pixel_size);
	point(&world_coord, cam->half_width - offsets.x, 
		cam->half_height - offsets.y, -1);
	inv = mat4x4_inverse(&cam->transform);
	pixel = mat4x4_cross_vec(&inv, &world_coord);
	point(&world_coord, 0, 0, 0);
	origin = mat4x4_cross_vec(&inv, &world_coord);
	d4sub(&direction, &pixel, &origin);
	vnormalize(&direction);
	return ((t_ray)
	{
		.origin = origin,
		.direction = direction
	});
}

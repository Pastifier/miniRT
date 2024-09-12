/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:23 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/13 02:43:30 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rtmath.h"
#include "objects.h"
#include "linear_algebra.h"
#include <stdio.h>
#include "matrix.h"
#include "mlx.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static void	setup_world_chapter7(t_world *w)
{
	t_mat4x4 transform_operations;
	t_light	light;

	point(&light.position,-10, 10, -10);
	color(&light.type.point.intensity, 1, 1, 1);

	// Initialize the walls
	t_object floor;
	plane(&floor, NULL, NULL);
	floor.material = default_material();
	color(&floor.material.color, 1.0, 1.0, 1.0);
	floor.material.specular = 0;

	t_object left_wall;
	plane(&left_wall, NULL, NULL);
	transform_operations = translation(0, 0, 5);
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	transform_operations = rotation_y(-(M_PI / 4));
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	transform_operations = rotation_x(M_PI / 2);
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	left_wall.material = floor.material;

	// t_object right_wall;
	// plane(&right_wall, NULL, NULL);
	// right_wall.transform = mat4x4_identity();
	// transform_operations = translation(0, 0, 5);
	// right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	// transform_operations = rotation_y(M_PI / 4);
	// right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	// transform_operations = rotation_x(M_PI / 2);
	// right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	// right_wall.material = floor.material;

	t_object middle;
	sphere(&middle, NULL, 1, NULL);
	middle.transform = mat4x4_identity();
	transform_operations = translation(-0.5, 1, 0.5);
	middle.transform = mat4x4_cross(&middle.transform, &transform_operations);
	middle.material = default_material();
	color(&middle.material.color, 0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	t_object right;
	sphere(&right, NULL, 1, NULL);
	right.transform = mat4x4_identity();
	transform_operations = translation(1.5, 0.5, -0.5);
	right.transform = mat4x4_cross(&right.transform, &transform_operations);
	transform_operations = scaling(0.5, 0.5, 0.5);
	right.transform = mat4x4_cross(&right.transform, &transform_operations);
	right.material = default_material();
	color(&right.material.color, 0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	t_object left;
	sphere(&left, NULL, 1, NULL);
	left.transform = mat4x4_identity();
	transform_operations = translation(-1.5, 1.0, -0.75);
	left.transform = mat4x4_cross(&left.transform, &transform_operations);
	transform_operations = scaling(0.33, 0.33, 0.33);
	left.transform = mat4x4_cross(&left.transform, &transform_operations);
	left.material = default_material();
	color(&left.material.color, 1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	world_add_light(w, &light);
	world_add_object(w, &floor);
	world_add_object(w, &left_wall);
	// world_add_object(w, &right_wall);
	world_add_object(w, &middle);
	world_add_object(w, &right);
	world_add_object(w, &left);
}

t_color	render_pixel(t_program *context, int x, int y)
{
	t_ray			r;
	t_color			c;

	r = ray_for_pixel(&context->camera, x, y);
	c = color_at(&context->world, &r);
	put_pixel(&context->canvas, x, y, c);
	return (c);
}

void	*render_row(void *arg)
{
	t_thread_data	*data = (t_thread_data *)arg;
	t_program		*context = data->context;
	t_camera		*cam = &context->camera;
	int				x;
	int				y;
	int				y_f;

	y = data->y;
	y_f = data->y_f;
	while (y < y_f)
	{
		x = 0;
		while(x < cam->hsize)
		{
			render_pixel(context, x, y);
			x+=SKIPPED_PIX;
		}
		y+=SKIPPED_PIX;
	}
	return (NULL);
}

void	*interpolate_routine(void *arg)
{
	t_thread_data	*data = (t_thread_data *)arg;

	interpolate_horizontal(data);
	interpolate_vertical(data);
	(void)data;
	return (NULL);
}

void	render_scene(t_program *context)
{
	int			y;
	t_camera	cam;
	t_world		w;


	setup_camera(&cam, M_PI / 3);
	t_double4 from;
	point(&from, -1, 1.0, -5);
	t_double4 to;
	point(&to, 0, 1, 0);
	t_double4 up;
	vector(&up, 0, 1, 0);
	t_mat4x4 t = view_transform(from, to, up);
	cam.transform = t;
	w.cam_inverse = mat4x4_inverse(&t);
	empty_world(&w);
	setup_world_chapter7(&w);

	// default_world(&w);

	y = -1;
	context->world = w;
	context->camera = cam;
	t_thread_data	threads[THREAD_NUM];
	while (++y < THREAD_NUM)
	{
		threads[y].id = y;
		threads[y].context = context;
		threads[y].y = y * (cam.vsize / THREAD_NUM);
		threads[y].y_f = (y + 1) * (cam.vsize / THREAD_NUM);
		threads[y].x = y * (cam.hsize / THREAD_NUM);			// ??
		threads[y].x_f = (y + 1) * (cam.hsize / THREAD_NUM);	// ??
		pthread_create(&threads[y].thread, NULL, render_row, &threads[y]);
	}
	while (y--)
		pthread_join(threads[y].thread, NULL);
	y = -1;
	while (++y < THREAD_NUM)
		pthread_create(&threads[y].thread, NULL, interpolate_routine, &threads[y]);
	while (y--)
		pthread_join(threads[y].thread, NULL);
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
}

// static void	setup_world_chapter7(t_world *w)
// {
// 	t_mat4x4 transform_operations;

// 	point(&w->lights[0].position, -10, 10, -10);
// 	color(&w->lights[0].type.point.intensity, 1, 1, 1);

// 	// Initialize the walls
// 	t_object floor;
// 	sphere(&floor, NULL, 1, NULL);
// 	floor.transform = scaling(10, 0.01, 10);
// 	floor.material = default_material();
// 	color(&floor.material.color, 1, 1.0, 1.0);
// 	floor.material.specular = 0;

// 	t_object left_wall;
// 	sphere(&left_wall, NULL, 1, NULL);
// 	transform_operations = translation(0, 0, 5);
// 	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
// 	transform_operations = rotation_y(-M_PI_4);
// 	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
// 	transform_operations = rotation_x(M_PI_2);
// 	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
// 	transform_operations = scaling(10, 0.01, 10);
// 	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
// 	left_wall.material = floor.material;

// 	t_object right_wall;
// 	sphere(&right_wall, NULL, 1, NULL);
// 	right_wall.transform = mat4x4_identity();
// 	transform_operations = translation(0, 0, 5);
// 	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
// 	transform_operations = rotation_y(M_PI_4);
// 	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
// 	transform_operations = rotation_x(M_PI_2);
// 	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
// 	transform_operations = scaling(10, 0.01, 10);
// 	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
// 	right_wall.material = floor.material;

// 	t_object middle;
// 	sphere(&middle, NULL, 1, NULL);
// 	middle.transform = mat4x4_identity();
// 	transform_operations = translation(-0.5, 1, 0.5);
// 	middle.transform = mat4x4_cross(&middle.transform, &transform_operations);
// 	middle.material = default_material();
// 	color(&middle.material.color, 0.1, 1, 0.5);
// 	middle.material.diffuse = 0.7;
// 	middle.material.specular = 0.3;

// 	t_object right;
// 	sphere(&right, NULL, 1, NULL);
// 	right.transform = mat4x4_identity();
// 	transform_operations = translation(1.5, 0.5, -0.5);
// 	right.transform = mat4x4_cross(&right.transform, &transform_operations);
// 	transform_operations = scaling(0.5, 0.5, 0.5);
// 	right.transform = mat4x4_cross(&right.transform, &transform_operations);
// 	right.material = default_material();
// 	color(&right.material.color, 0.5, 1, 0.1);
// 	right.material.diffuse = 0.7;
// 	right.material.specular = 0.3;

// 	t_object left;
// 	sphere(&left, NULL, 1, NULL);
// 	left.transform = mat4x4_identity();
// 	transform_operations = translation(-1.5, 1.0, -0.75);
// 	left.transform = mat4x4_cross(&left.transform, &transform_operations);
// 	transform_operations = scaling(0.33, 0.33, 0.33);
// 	left.transform = mat4x4_cross(&left.transform, &transform_operations);
// 	left.material = default_material();
// 	color(&left.material.color, 1, 0.8, 0.1);
// 	left.material.diffuse = 0.7;
// 	left.material.specular = 0.3;

// 	world_add_light(w, &w->lights[0]);
// 	world_add_object(w, &floor);
// 	world_add_object(w, &left_wall);
// 	world_add_object(w, &right_wall);
// 	world_add_object(w, &middle);
// 	world_add_object(w, &right);
// 	world_add_object(w, &left);
// }

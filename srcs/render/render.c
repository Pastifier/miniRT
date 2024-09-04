/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:23 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/04 14:11:54 by melshafi         ###   ########.fr       */
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
	t_mat4x4 transformation;
	t_mat4x4 transform_operations;

	transformation = scaling(0.5, 0.5, 0.5);
	sphere(&w->objects[0], NULL, 1, NULL);
	color(&w->objects[0].material.color, 0.8, 1.0, 0.6);
	w->objects[0].material.diffuse = 0.7;
	w->objects[0].material.specular = 0.2;

	sphere(&w->objects[1], NULL, 1, NULL);
	w->objects[1].transform = transformation;

	point(&w->lights[0].position, -10, 10, -10);
	color(&w->lights[0].type.point.intensity, 1, 1, 1);

	// Initialize the walls
	t_object floor;
	sphere(&floor, NULL, 1, NULL);
	floor.transform = scaling(10, 0.01, 10);
	floor.material = default_material();
	color(&floor.material.color, 1, 0.9, 0.9);
	floor.material.specular = 0;
	w->objects[0] = floor;

	t_object left_wall;
	sphere(&left_wall, NULL, 1, NULL);
	transform_operations = translation(0, 0, 5);
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	transform_operations = rotation_y(-M_PI_4);
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	transform_operations = rotation_x(M_PI_2);
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	transform_operations = scaling(10, 0.01, 10);
	left_wall.transform = mat4x4_cross(&left_wall.transform, &transform_operations);
	left_wall.material = floor.material;
	w->objects[1] = left_wall;

	t_object right_wall;
	sphere(&right_wall, NULL, 1, NULL);
	right_wall.transform = mat4x4_identity();
	transform_operations = translation(0, 0, 5);
	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	transform_operations = rotation_y(M_PI_4);
	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	transform_operations = rotation_x(M_PI_2);
	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	transform_operations = scaling(10, 0.01, 10);
	right_wall.transform = mat4x4_cross(&right_wall.transform, &transform_operations);
	right_wall.material = floor.material;
	w->objects[2] = right_wall;

	t_object middle;
	sphere(&middle, NULL, 1, NULL);
	middle.transform = mat4x4_identity();
	transform_operations = translation(-0.5, 1, 0.5);
	middle.transform = mat4x4_cross(&middle.transform, &transform_operations);
	middle.material = default_material();
	color(&middle.material.color, 0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	w->objects[3] = middle;

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
	w->objects[4] = right;

	t_object left;
	sphere(&left, NULL, 1, NULL);
	left.transform = mat4x4_identity();
	transform_operations = translation(-1.5, 0.33, -0.75);
	left.transform = mat4x4_cross(&left.transform, &transform_operations);
	transform_operations = scaling(0.33, 0.33, 0.33);
	left.transform = mat4x4_cross(&left.transform, &transform_operations);
	left.material = default_material();
	color(&left.material.color, 1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;
	w->objects[5] = left;

	w->num_objects = 6;
	w->num_lights = 1;
}

void	*render_row(void *arg)
{
	t_thread_data	*data = (t_thread_data *)arg;
	t_program		*context = data->context;
	t_camera		*cam = &context->camera;
	t_world			*w = &context->world;
	t_ray			r;
	t_color			c;
	int				x;
	int				y;

	x = data->start.x;
	y = data->start.y;
	while (y < data->end.y)
	{
		r = ray_for_pixel(cam, x, y);
		c = color_at(w, &r);
		put_pixel(&context->canvas, x, y, &c);
		x++;
		if (x == cam->hsize)
		{
			x = 0;
			y++;
		}
	}

	return (NULL);
}

void	render_scene(t_program *context)
{
	int			y;
	t_camera	cam;
	t_world		w;


	setup_camera(&cam, M_PI / 3);
	t_double4 from;
	point(&from, 0, 0, -3);
	t_double4 to;
	point(&to, 0, 0, 1);
	t_double4 up;
	vector(&up, 0, 1, 0);
	t_mat4x4 t = view_transform(from, to, up);
	cam.transform = t;
	w.cam_inverse = mat4x4_inverse(&t);
	setup_world_chapter7(&w);

	y = 0;
	context->world = w;
	context->camera = cam;
	t_thread_data	threads[cam.vsize];
	while (y < cam.vsize)
	{
		threads[y].id = y;
		threads[y].context = context;
		threads[y].start = row2(0, y);
		threads[y].end = row2(cam.hsize, y + 1);
		pthread_create(&threads[y].thread, NULL, render_row, &threads[y]);
		y++;
	}
	while (y--)
		pthread_join(threads[y].thread, NULL);
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
	printf("Done rendering\n");
}

void render_sphere(t_program *context)
{
	t_color	lit_color;
	t_object s;
	double wall_z = 10.0;
	double wall_size = 7.0;
	double pixel_size = wall_size / WIN_WIDTH;
	double half = wall_size / 2.0;
	t_double4 ray_origin;
	vector(&ray_origin, 0.0, 0.0, -5.0);
	t_double4 center;
	point(&center, 0.0, 0.0, 0.0);
	sphere(&s, &(center), 1.0, NULL);
	color(&s.material.color, 1.0, 0.2, 1.0);
	t_light light = default_point_light();

	//Try out the different transformations
	// t_mat4x4 scaling_matrix = scaling(0.5, 1.0, 1.0);
	// t_mat4x4 rotation_matrix = rotation_z(M_PI / 4.0);
	// t_mat4x4 shearing_matrix = shearing(1.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	s.transform = scaling(1.0, 0.5, 1.0);
	// s.transform = scaling(0.5, 1.0, 1.0);
	// s.transform = mat4x4_cross(&scaling_matrix, &rotation_matrix);
	// s.transform = mat4x4_cross(&scaling_matrix, &shearing_matrix);

	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		// Compute the world y coordinate
		double world_y = half - pixel_size * y;
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			// Compute the world x coordinate
			double world_x = -half + pixel_size * x;

			// Target point on the wall
			t_double4 position;
			point(&position, world_x, world_y, wall_z);

			// Create a ray from the origin through this point
			t_double4 direction;
			d4sub(&direction, &position, &ray_origin);
			vnormalize(&direction);

			t_ray ray;
			ray_create(&ray, &ray_origin, &direction); //

		//	ft_bzero(&ray.itx, sizeof(t_intersections)); // Emran: You need to reset the intersections for each ray! They're different entities ^^ <3

			intersect_sphere(&ray, &s); //
			if (ray.itx.count > 0)
			{
				t_color c;
				color(&c, 1.0, 0.0, 0.0);
				t_intersection *itx;
				itx = get_hit(&ray.itx);
				if (itx == NULL)
					continue ;

				t_double4 point_of_intersection;
				ray_position(&point_of_intersection, &ray, itx->t);

				t_double4 norm;
				norm = sphere_normal_at(&s, &point_of_intersection);

				t_double4 eye_v;
				eye_v = ray.direction;
				d4negate(&eye_v);

				// printf("Point of intersection: %0.3f, %0.3f, %0.3f\n", point_of_intersection.x, point_of_intersection.y, point_of_intersection.z);
				// printf("eye_v: %0.3f, %0.3f, %0.3f\n", eye_v.x, eye_v.y, eye_v.z);
				// printf("norm: %0.3f, %0.3f, %0.3f\n", norm.x, norm.y, norm.z);

				lit_color = lighting(&s.material, &light, &point_of_intersection, &eye_v, &norm);
				put_pixel(&context->canvas, x, y, &lit_color);
			}
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
	printf("Done rendering\n");
}

void render_clock(t_program *context)
{
	int center_x = WIN_WIDTH / 2;
	int center_y = WIN_HEIGHT / 2;

	int num_hours = 12;
	double angle_increment = 2 * M_PI / num_hours;
	double initial_radius = (center_y / 2.0);
	t_double4 p;
	point(&p, initial_radius, 0.0, 0.0);
	t_mat4x4 scale_matrix = scaling(0.5, 0.5, 0.5);
	p = mat4x4_cross_vec(&scale_matrix, &p);
	for (int i = 0; i < num_hours; i++)
	{
		t_mat4x4 rotation_matrix = rotation_z(i * angle_increment);
		t_double4 rotated_p = mat4x4_cross_vec(&(rotation_matrix), &p);

		rotated_p.x += center_x;
		rotated_p.y += center_y;

		if ((int)rotated_p.x >= 0 && (int)rotated_p.x < WIN_WIDTH && (int)rotated_p.y >= 0 && (int)rotated_p.y < WIN_HEIGHT)
		{
			t_color c;
			color(&c, 1.0, 1.0, 1.0);
			put_pixel(&context->canvas, (int)rotated_p.x, (int)rotated_p.y, &c);
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
}

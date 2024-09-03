/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:23 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/03 16:41:30 by melshafi         ###   ########.fr       */
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

void	render_scene(t_program *context)
{
	int			x;
	int			y;
	t_camera	cam;
	t_world		w;


	// t_object floor;
	// t_object left_wall;
	// t_object right_wall;
	// t_object middle;
	// t_object right;
	// t_object left;
	// t_material floor_material;
	// t_material left_wall_material;
	// t_material right_wall_material;
	// t_material middle_material;
	// t_material right_material;
	// t_material left_material;
	// t_mat4x4 floor_transform;
	// t_mat4x4 left_wall_transform;
	// t_mat4x4 right_wall_transform;
	// t_mat4x4 middle_transform;
	// t_mat4x4 right_transform;
	// t_mat4x4 left_transform;
	// t_color floor_color;
	// t_color left_wall_color;
	// t_color right_wall_color;
	// t_color middle_color;
	// t_color right_color;
	// t_color left_color;

	// color(&floor_color, 1.0, 0.9, 0.9);
	// color(&left_wall_color, 0.9, 1.0, 0.9);
	// color(&right_wall_color, 0.9, 0.9, 1.0);
	// color(&middle_color, 0.1, 1.0, 0.5);
	// color(&right_color, 0.5, 1.0, 0.1);
	// color(&left_color, 0.5, 0.1, 1.0);

	// floor_material = material(&floor_color, 0.1, 0.9, 0.9, 0.0);
	// left_wall_material = material(&left_wall_color, 0.1, 0.9, 0.9, 0.0);
	// right_wall_material = material(&right_wall_color, 0.1, 0.9, 0.9, 0.0);
	// middle_material = material(&middle_color, 0.1, 0.9, 0.9, 0.0);
	// right_material = material(&right_color, 0.1, 0.9, 0.9, 0.0);
	// left_material = material(&left_color, 0.1, 0.9, 0.9, 0.0);

	// t_mat4x4 scaling_matrix = scaling(10.0, 0.01, 10.0);
	// t_mat4x4 rotation_matrix = rotation_y(M_PI / 4);
	// floor_transform = mat4x4_cross(&scaling_matrix, &rotation_matrix);
	// left_wall_transform = mat4x4_cross(&scaling_matrix, &rotation_matrix);
	// right_wall_transform = mat4x4_cross(&scaling_matrix, &rotation_matrix);
	// t_mat4x4 translation_matrix = translation(0.0, 0.0, 5.0);
	// t_mat4x4 scaling_matrix2 = scaling(10.0, 0.01, 10.0);
	// middle_transform = mat4x4_cross(&translation_matrix, &scaling_matrix2);
	// right_transform = mat4x4_cross(&translation_matrix, &scaling_matrix2);
	// left_transform = mat4x4_cross(&translation_matrix, &scaling_matrix2);

	// sphere(&floor, NULL, 0.0, &floor_transform);
	// sphere(&left_wall, NULL, 0.0, &left_wall_transform);
	// sphere(&right_wall, NULL, 0.0, &right_wall_transform);
	// sphere(&middle, NULL, 0.0, &middle_transform);
	// sphere(&right, NULL, 0.0, &right_transform);
	// sphere(&left, NULL, 0.0, &left_transform);
	// floor.material = floor_material;
	// left_wall.material = left_wall_material;
	// right_wall.material = right_wall_material;
	// middle.material = middle_material;
	// right.material = right_material;
	// left.material = left_material;

	// empty_world(&w);
	// t_light light = default_point_light();
	// world_add_light(&w, &light);
	// world_add_object(&w, &floor);
	// world_add_object(&w, &left_wall);
	// world_add_object(&w, &right_wall);
	// world_add_object(&w, &middle);
	// world_add_object(&w, &right);
	// world_add_object(&w, &left);
	default_world(&w);
	setup_camera(&cam, M_PI / 3);
	t_double4 from;
	point(&from, 0, 1.5, 5);
	t_double4 to;
	point(&to, 0, 1, 0);
	t_double4 up;
	vector(&up, 0, 1, 0);
	cam.transform = view_transform(from, to, up);

	y = 0;
	while (y < cam.vsize)
	{
		x = 0;
		while (x < cam.hsize)
		{
			t_ray		r;
			t_color		c;
			r = ray_for_pixel(&cam, x, y);
			c = color_at(&w, &r);
			put_pixel(&context->canvas, x, y, &c);
			x++;
		}
		y++;
	}
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

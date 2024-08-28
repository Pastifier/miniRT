/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:23:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 04:53:37 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "log.h"
#include <stdlib.h>
#include <math.h>

void	this_is_just_here_to_segment_functions_into_sections(void)
{
	return ;
}

void	init_program(int argc, char **argv, t_program *program)
{
	(void)argv;
	if (argc != 2)
		(write_error("Need to have a scene file (`*.rt`)"), (void)exit(2));
	program->mlx = mlx_init();
	if (!program->mlx)
		(write_error("Couldn't init mlx"), (void)exit(2));
	program->win = mlx_new_window(program->mlx, WIN_WIDTH, WIN_HEIGHT, "mRT");
	if (!program->win)
		(free(program->mlx), write_error("Couldn't init mlx"),
			(void)exit(2));
	program->img.img = mlx_new_image(program->mlx, WIN_WIDTH, WIN_HEIGHT);
	program->img.addr = mlx_get_data_addr(program->img.img,
			&program->img.bits_per_pixel, &program->img.line_length,
			&program->img.endian);
	init_camera(&program->camera);
}

//void	init_camera(t_camera *camera)
//{
//	t_vector3	operations;

//	camera->center = (t_vector3){0, 0, 0};
//	camera->focal_length = 1.0;
//	camera->viewport_height = 2.0;
//	camera->viewport_width = camera->viewport_height
//			* ((double)WIN_WIDTH / (double)WIN_HEIGHT);
//	camera->viewport_u = (t_vector3){camera->viewport_width, 0, 0};
//	camera->viewport_v = (t_vector3){0, -camera->viewport_height, 0};
//	camera->pixel_delta_u = vec3_scaleby(camera->viewport_u, 1.0 / WIN_WIDTH);
//	camera->pixel_delta_v = vec3_scaleby(camera->viewport_v, 1.0 / WIN_HEIGHT);
//	this_is_just_here_to_segment_functions_into_sections();
//	operations = vec3_subtract(camera->center,
//		(t_vector3){0, 0, camera->focal_length});
//	operations = vec3_subtract(operations, vec3_scaleby(camera->viewport_u, 0.5));
//	operations = vec3_subtract(operations, vec3_scaleby(camera->viewport_v, 0.5));
//	camera->cartesian_upper_left = operations;
//	this_is_just_here_to_segment_functions_into_sections();
//	operations = vec3_add(camera->pixel_delta_u, camera->pixel_delta_v);
//	operations = vec3_scaleby(operations, 0.5);
//	camera->cartesian_shift = vec3_add(camera->cartesian_upper_left, operations);
//}

void	init_camera(t_camera *camera)
{
	camera->center = (t_vector3){0, 0, 0};
	camera->up = (t_vector3){0, 1, 0};
	camera->lookat = (t_vector3){0, 0, 1};
	camera->right = (t_vector3){1, 0, 0};
	camera->focal_length = 1.0f;
	camera->fov = 100.0f;
	camera->aspect_ratio = 16.0f / 9.0f;
	camera->viewport_height = camera->focal_length * tanf(camera->fov * 0.5 * (M_PI / 180.0f)) * 2;
	camera->viewport_width = camera->viewport_height * camera->aspect_ratio;
	camera->bottom_left_local = (t_vector3){-camera->viewport_width / 2, -camera->viewport_height / 2, camera->focal_length};
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:23:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 13:51:45 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "ray.h"
#include "camera.h"
#include "log.h"
#include "matrix.h"
#include "objects.h"
#include "rendering.h"
#include <stdlib.h>
#include <math.h>

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
	program->num_objects = 3;
	program->objects = malloc(sizeof(t_object) * program->num_objects);
	program->objects[0] = create_sphere((t_vector3){1, 5, 5}, 0.5, 0xFF0000);
	program->objects[1] = create_sphere((t_vector3){0, 10, -100.5}, 100, 0x000000);
	program->objects[2] = create_sphere((t_vector3){1, 3, 5}, 0.5, 0x0000FF);
	init_camera(&program->camera);
}

void	init_camera(t_camera *camera)
{
	camera->center = (t_vector3){0, 0, 0};
	camera->up = (t_vector3){0, 1, 0};
	camera->lookat = (t_vector3){0, 0, 1};
	camera->right = (t_vector3){1, 0, 0};
	camera->focal_length = 2.0f;
	camera->fov = 70.0f;
	camera->aspect_ratio = 16.0f / 9.0f;
}

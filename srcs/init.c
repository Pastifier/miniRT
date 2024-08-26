/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:23:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 16:46:59 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "log.h"
#include <stdlib.h>

static void	init_viewport(t_program *program)
{
	program->img.aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	program->camera.focal_length = 1.0;
	program->camera.viewport_height = 2.0;
	program->camera.viewport_width = program->img.aspect_ratio
		* program->camera.viewport_height;
	program->camera.origin = (t_vector3){0, 0, 0};
	program->camera.viewport_u = (t_vector3){program->camera.viewport_width, 0, 0};
	program->camera.viewport_v = (t_vector3){0, -program->camera.viewport_height, 0};
	program->camera.pixel_delta_u = vec3_scaleby(program->camera.viewport_u,
			1.0 / WIN_WIDTH);
	program->camera.pixel_delta_v = vec3_scaleby(program->camera.viewport_v,
			1.0 / WIN_HEIGHT);
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
	init_viewport(program);
}

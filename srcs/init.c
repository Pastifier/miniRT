/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:23:58 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 11:54:59 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "log.h"
#include <stdlib.h>

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
}

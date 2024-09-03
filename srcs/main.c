/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/03 15:04:27 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "minirt.h"
#include "macros.h"
#include "linear_algebra.h"
#include <stdio.h>
#include "matrix.h"
#include "mlx.h"
#include "objects.h"
#include "colors.h"
#include "mlx.h"

int main(void)
{
	// t_program	context;

	t_camera	cam;
	setup_camera(&cam, M_PI / 2);
	printf("Pixel size: %f\n", cam.pixel_size);
	// context.mlx = mlx_init();
	// context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	// canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	// render_sphere(&context);
	// mlx_loop(context.mlx);
	return (0);
}

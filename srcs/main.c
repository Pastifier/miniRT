/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/15 02:12:49 by ebinjama         ###   ########.fr       */
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
#include "keys.h"

int main(void)
{
	t_program	context;
	t_camera	cam;
	t_world		w;

	setup_camera(&cam, M_PI / 3);

	empty_world(&w);
	setup_world_chapter7(&w);

	context.world = w;
	context.camera = cam;

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	render_new_frame(&context);

	mlx_hook(context.win, ON_KEYDOWN, 1L, key_hook, &context);
	mlx_loop(context.mlx);

	return (0);
}


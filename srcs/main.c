/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 20:08:12 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "miniRT.h"
#include "macros.h"
#include "linear_algebra.h"
#include <stdio.h>
#include "matrix.h"

#define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f)\n", v.x, v.y, v.z)

#include "mlx.h"

int main(void)
{
	t_program	context;

	context.mlx = mlx_init();
	// iferr: exit
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	// iferr: exit
	canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	render_sphere(&context);
	mlx_loop(context.mlx);
	return (0);
}

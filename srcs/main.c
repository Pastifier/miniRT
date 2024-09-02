/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/02 16:37:35 by melshafi         ###   ########.fr       */
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

#define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f)\n", v.x, v.y, v.z)

#include "mlx.h"

int main(void)
{
	t_program	context;

	// t_point_light light = default_light();
	// t_material material = default_material();
	// t_sphere s;
	// t_double4 center;
	// t_double4 eye_v;
	// t_double4 normal_v;
	// t_color result;
	// light.position.x = 0;
	// light.position.y = 0;
	// vector(&normal_v, 0, 0, -1);
	// // vector(&eye_v, 0, 0, -1);
	// vector(&eye_v, 0, sqrt(2) / 2, sqrt(2) / 2);
	// point(&center, 0, 0, 0);
	// sphere(&s, &center, 1, NULL);
	// result = lighting(&material, &light, &center, &eye_v, &normal_v);
	// PRINT_VECTOR(result.set);
	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	render_sphere(&context);
	mlx_loop(context.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/10 02:37:54 by ebinjama         ###   ########.fr       */
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
#include "rtmath.h"
#include "mlx.h"

pthread_mutex_t	mutex;

int main(void)
{
	t_program	context;

	pthread_mutex_init(&mutex, NULL);

	// t_world	w;
	// default_world(&w);
	// t_object	p;
	// t_mat4x4	transform_operations;
	// transform_operations = translation(0, -1, 0);
	// plane(&p, NULL, &transform_operations);
	// p.material.reflective = 0.5;
	// world_add_object(&w, &p);
	// t_ray	r;
	// t_double4	origin;
	// t_double4	direction;
	// point(&origin, 0, 0, -3);
	// vector(&direction, 0, -sqrt(2)/2, sqrt(2)/2);
	// ray_create(&r, &origin, &direction);
	// t_intersection	itx;
	// itx.t = sqrt(2);
	// itx.object = &p;
	// t_itx_computation	comps;
	// comps = prepare_computations(itx, &r);
	// t_color	c;
	// c = reflected_color(&w, &comps, 1);
	// printf("Color: %f %f %f\n", c.r, c.g, c.b);

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	printf("Canvas address %p\n", context.canvas.addr);
	printf("Line length: %d\n", context.canvas.line_length);
	render_scene(&context);
	mlx_loop(context.mlx);
	// mlx_key_hook(context.win, key_hook, &context);
	return (0);
}

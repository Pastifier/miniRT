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
	// empty_world(&w);

	// t_light	l;
	// l = default_point_light();
	// world_add_light(&w, &l);

	// t_object	s1;
	// t_mat4x4	transform1;
	// transform1 = scaling(2, 2, 2);
	// sphere(&s1, NULL, 1, &transform1);
	// s1.material.transparency = 1.0;
	// s1.material.refractive_index = 1.5;
	// world_add_object(&w, &s1);

	// t_object	s2;
	// t_mat4x4	transform2;
	// transform2 = scaling(0, 0, -0.25);
	// sphere(&s2, NULL, 1, &transform2);
	// s2.material.transparency = 1.0;
	// s2.material.refractive_index = 2.0;
	// world_add_object(&w, &s2);

	// t_object	s3;
	// t_mat4x4	transform3;
	// transform3 = scaling(0, 0, 0.25);
	// sphere(&s3, NULL, 1, &transform3);
	// s3.material.transparency = 1.0;
	// s3.material.refractive_index = 2.5;
	// world_add_object(&w, &s3);

	// t_ray	r;
	// point(&r.origin, 0, 0, -4);
	// vector(&r.direction, 0, 0, 1);

	// t_intersections	itx;
	// itx.data[0].t = 2;
	// itx.data[0].object = &s1;
	// itx.data[1].t = 2.75;
	// itx.data[1].object = &s2;
	// itx.data[2].t = 3.25;
	// itx.data[2].object = &s3;
	// itx.data[3].t = 4.75;
	// itx.data[3].object = &s2;
	// itx.data[4].t = 5.25;
	// itx.data[4].object = &s3;
	// itx.data[5].t = 6;
	// itx.data[5].object = &s1;
	// itx.count = 6;

	// t_itx_computation	comps;
	// comps = prepare_computations(&itx.data[0], &r, &itx);
	// printf("n1: %f\n", comps.n1);
	// printf("n2: %f\n\n", comps.n2);

	// comps = prepare_computations(&itx.data[1], &r, &itx);
	// printf("n1: %f\n", comps.n1);
	// printf("n2: %f\n\n", comps.n2);

	// comps = prepare_computations(&itx.data[2], &r, &itx);
	// printf("n1: %f\n", comps.n1);
	// printf("n2: %f\n\n", comps.n2);

	// comps = prepare_computations(&itx.data[3], &r, &itx);
	// printf("n1: %f\n", comps.n1);
	// printf("n2: %f\n\n", comps.n2);

	// comps = prepare_computations(&itx.data[4], &r, &itx);
	// printf("n1: %f\n", comps.n1);
	// printf("n2: %f\n\n", comps.n2);

	// comps = prepare_computations(&itx.data[5], &r, &itx);
	// printf("n1: %f\n", comps.n1);
	// printf("n2: %f\n\n", comps.n2);

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

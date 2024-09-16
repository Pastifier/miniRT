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

	t_world	w;
	empty_world(&w);
	t_light	l;
	l = default_point_light();
	world_add_light(&w, l);
	t_object	s1;
	s1 = default_sphere();
	s1.material.refraction = 1.5;
	t_mat4x4	transform1;
	transform1 = scaling(2, 2, 2);
	s1.transform = transform1;
	world_add_object(&w, s1);
	t_object	s2;
	s2 = default_sphere();
	t_mat4x4	transform2;
	transform2 = scaling(0, 0, -0.25);
	s2.transform = transform2;
	s1.material.refraction = 2.0;
	world_add_object(&w, s2);
	t_object	s3;
	s3 = default_sphere();
	t_mat4x4	transform3;
	transform3 = scaling(0, 0, 0.25);
	s3.transform = transform3;
	s1.material.refraction = 2.5;
	world_add_object(&w, s3);

	t_ray	r;
	point(&r.origin, 0, 0, -4);
	vector(&r.direction, 0, 0, 1);
	t_intersections	itx;
	itx.data[0].t = 2;
	itx.data[0].object = &s1;
	itx.data[1].t = 2.75;
	itx.data[1].object = &s2;
	itx.data[2].t = 3.25;
	itx.data[2].object = &s3;
	t_itx_computation	comps;
	comps = prepare_computations(itx.data[0], &r);
	

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

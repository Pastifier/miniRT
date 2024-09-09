/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:50:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/08 23:38:42 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "miniRT.h"
#include "render.h"
#include "rtmath.h"
#include "world.h"
#include "matrix.h"
#include "macros.h"
#include "linear_algebra.h"
#include "colors.h"
#include "debug.h"
#include "intersection.h"
#include "threads.h"
#include "mlx.h"
#include "defaults.h"
#include "libft.h"

/*--- Garbage from before I ascended to human status ---*/

void	draw_clock(t_program *context);
void	fill_canvas(t_canvas *canvas, uint32_t color);
void	draw_sphere_using_rt(t_program *context, t_obj *sphere, t_light *plight);
void	world_from_chapter_7(void);

/*--- Utilities ---*/

void	intersection_test(t_ray *r, t_obj *obj,
		bool (*itx_fun)(t_ray *, t_obj *, t_intersections *));

void	normal_at_test(t_double4 *p, t_obj *obj,
		t_double4 (*local_normal_at)(t_obj *, t_double4 *));

/*--- Cylinders ---*/

void	test_rays_should_miss_cylinder(void);
void	test_rays_should_intersect_cylinder(void);
void	test_normal_on_cy(void);
void	test_intersections_on_truncated_cy(void);
void	test_intersections_on_capped_cy(void);
void	test_normal_on_cy_caps(void);
void	test_render_simple_cy(void);
void	test_render_transformed_cy(void);

# endif // !TESTS_H
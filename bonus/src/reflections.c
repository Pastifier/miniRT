/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:47:21 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/08 10:47:36 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

t_color	reflected_color(t_world *world, t_itx_computation *comps, int depth)
{
	t_ray		r;
	t_color		reflected_color;
	t_vec4s		reflectv;
	t_vec4s		reflect_origin;
	t_vec4s		offset;

	color_init(&reflected_color, 0.0, 0.0, 0.0);
	if (depth <= 0 || comps->obj->material.reflective <= 0.0)
		return (reflected_color);
	reflectv = comps->reflectv;
	lag_vec4s_scaleby(&offset, comps->normalv, EPSILON);
	lag_vec4s_add(&reflect_origin, &comps->over_point, &offset);
	ray_create(&r, &reflect_origin, &reflectv);
	reflected_color = color_at(world, &r, depth - 1);
	color_scaleby(&reflected_color, &reflected_color, comps->obj->material.reflective);
	return (reflected_color);
}

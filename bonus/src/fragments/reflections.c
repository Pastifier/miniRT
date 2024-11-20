/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:47:21 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/20 10:25:45 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

t_color	reflected_color(t_world *world, t_comps *comps, int depth)
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
	color_scaleby(&reflected_color, &reflected_color,
		comps->obj->material.reflective);
	return (reflected_color);
}

static void	check_for_refref_init(t_comps *comps, t_color *return_color)
{
	color_init(return_color, 0.0, 0.0, 0.0);
	if (comps->obj->material.reflective > 0.0f)
		color_scaleby(return_color, return_color,
			1.0f - comps->obj->material.reflective);
	if (comps->obj->material.transparency > 0.0f)
		color_scaleby(return_color, return_color,
			1.0f - comps->obj->material.transparency);
}

t_color	check_for_refref(t_world *world, t_comps *comps, int depth)
{
	double		schlick_value;
	t_color		reflection_result;
	t_color		refraction_result;
	t_color		return_color;

	reflection_result = reflected_color(world, comps, depth);
	refraction_result = refracted_color(world, comps, depth);
	check_for_refref_init(comps, &return_color);
	if (comps->obj->material.reflective > 0.0f
		&& comps->obj->material.transparency > 0.0f)
	{
		schlick_value = schlick(comps);
		color_scaleby(&reflection_result,
			&reflection_result, 1.0f - schlick_value);
		color_scaleby(&reflection_result, &reflection_result, schlick_value);
	}
	if (comps->obj->material.reflective > 0.0f)
		color_add(&return_color, &return_color, &reflection_result);
	if (comps->obj->material.transparency > 0.0f)
		color_add(&return_color, &return_color, &refraction_result);
	return (return_color);
}

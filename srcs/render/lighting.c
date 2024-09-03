/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:32 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/03 13:41:54 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "objects.h"
#include <stdio.h>

t_color	lighting(t_material *material, t_light *light, t_double4 *point, t_double4 *eye_v, t_double4 *normal)
{
	t_double4	light_v;
	t_double4	reflect_v;
	t_color		effective_color;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		return_color;
	double		reflect_eye_dot;
	double		light_dot_normal;
	double		factor;

	cblend(&effective_color, &material->color, &light->type.point.intensity);
	d4sub(&light_v, &light->position, point);
	vnormalize(&light_v);
	cscale(&ambient, &effective_color, material->ambient);
	normal->w = 0;
	light_dot_normal = vdot(&light_v, normal);

	if (light_dot_normal < 0)
	{
		color(&diffuse, 0.0, 0.0, 0.0);
		color(&specular, 0.0, 0.0, 0.0);
	} else
	{
		cscale(&diffuse, &effective_color, material->diffuse * light_dot_normal);
		d4negate(&light_v);
		reflect_v = reflect(&light_v, normal);
		reflect_eye_dot = vdot(&reflect_v, eye_v);
		if (reflect_eye_dot <= 0)
			color(&specular, 0.0, 0.0, 0.0);
		else
		{
			factor = pow(reflect_eye_dot, material->shininess);
			cscale(&specular, &light->type.point.intensity, material->specular * factor);
		}
	}
	cadd(&return_color, &ambient, &diffuse);
	cadd(&return_color, &return_color, &specular);
	return (return_color);
}

t_color	shade_hit(t_world *world, t_itx_computation *comps)
{
	t_color		lighting_result;
	t_color		return_color;

	color(&return_color, 0.0, 0.0, 0.0);
	for (int i = 0; i < world->num_lights; i++)
	{
		lighting_result = lighting(&comps->obj->material, &world->lights[i], &comps->p, &comps->eyev, &comps->normalv);
		cadd(&return_color, &return_color, &lighting_result);
	}
	return (return_color);
}

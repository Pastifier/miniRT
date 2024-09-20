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
#include "macros.h"
#include <stdio.h>

t_color	lighting(t_material *material, t_light *light, t_double4 *point, t_double4 *eye_v, t_double4 *normal, bool in_shadow)
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
	if (in_shadow)
	{
		color(&diffuse, 0.0, 0.0, 0.0);
		color(&specular, 0.0, 0.0, 0.0);
	}
	cadd(&return_color, &ambient, &diffuse);
	cadd(&return_color, &return_color, &specular);
	return (return_color);
}

bool	is_shadowed(t_world *world, t_double4 *point, t_light *light)
{
	t_double4		v;
	t_ray			r;
	t_intersection	*itx;
	
	d4sub(&v, &light->position, point);
	ray_create(&r, point, &v);
	r.itx = intersect_world(world, &r);
	itx = get_hit(&r.itx);
	if (itx && itx->t < vmag(&v))
		return (true);
	return (false);	
}

t_color	reflected_color(t_world *world, t_itx_computation *comps, int depth)
{
	t_color		c;
	t_ray		r;
	t_color		reflected_color;
	t_double4	reflectv;
	t_double4	reflect_origin;
	t_double4	offset;

	color(&c, 0.0, 0.0, 0.0);
	if (depth <= 0 || comps->obj->material.reflective <= 0.0)
		return (c);
	reflectv = comps->reflectv;
	d4mul(&offset, &comps->normalv, EPSILON);
	d4add(&reflect_origin, &comps->over_point, &offset);
	ray_create(&r, &reflect_origin, &reflectv);
	reflected_color = color_at(world, &r, depth - 1);
	cscale(&reflected_color, &reflected_color, comps->obj->material.reflective);
	return (reflected_color);
}

t_color	shade_hit(t_world *world, t_itx_computation *comps, int depth)
{
	t_color		lighting_result;
	t_color		reflection_result;
	t_color		refraction_result;
	t_color		return_color;
	bool		in_shadow;
	
	color(&return_color, 0.0, 0.0, 0.0);
	for (int i = 0; i < world->num_lights; i++)
	{
		in_shadow = is_shadowed(world, &comps->over_point, &world->lights[i]);
		lighting_result = lighting(&comps->obj->material, &world->lights[i], &comps->over_point, &comps->eyev, &comps->normalv, in_shadow);
		cadd(&return_color, &return_color, &lighting_result);
	}
	reflection_result = reflected_color(world, comps, depth);
	refraction_result = refracted_color(world, comps, depth);
	if (comps->obj->material.reflective > 0.0)
		cscale(&return_color, &return_color, 1.0 - comps->obj->material.reflective);
	if (comps->obj->material.transparency > 0.0)
		cscale(&return_color, &return_color, 1.0 - comps->obj->material.transparency);
	double schlick_value = schlick(comps);
	if (comps->obj->material.reflective > 0.0 && comps->obj->material.transparency > 0.0)
	{
		cscale(&reflection_result, &reflection_result, 1.0 - schlick_value);
		cscale(&reflection_result, &reflection_result, schlick_value);
	}
	cadd(&return_color, &return_color, &reflection_result);
	cadd(&return_color, &return_color, &refraction_result);
	cclamp(&return_color);
	return (return_color);
}

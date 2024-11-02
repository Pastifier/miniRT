/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:36:57 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/02 22:31:10 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

t_color	lighting(t_material *material, t_light *light, t_vec4s *point, t_vec4s *eye_v, t_vec4s *normal, bool in_shadow)
{
	t_vec4s	light_v;
	t_vec4s	reflect_v;
	t_color		effective_color;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		return_color;
	double		reflect_eye_dot;
	double		light_dot_normal;
	double		factor;

	color_blend(&effective_color, &material->color, &light->specs.point.intensity);
	lag_vec4s_sub(&light_v, &light->pos, point);
	lag_vec4s_normalize(&light_v);
	color_scaleby(&ambient, &effective_color, material->ambient);
	normal->w = 0;
	light_dot_normal = lag_vec4s_dot_ret(&light_v, normal);

	if (light_dot_normal < 0)
	{
		color_init(&diffuse, 0.0, 0.0, 0.0);
		color_init(&specular, 0.0, 0.0, 0.0);
	} else
		color_scaleby(&diffuse, &effective_color, material->diffuse * light_dot_normal);
	lag_vec4s_negate(&light_v);
	reflect_v = reflect(&light_v, normal);
	reflect_eye_dot = lag_vec4s_dot_ret(&reflect_v, eye_v);
	if (reflect_eye_dot <= 0)
		color_init(&specular, 0.0, 0.0, 0.0);
	else
	{
		factor = pow(reflect_eye_dot, material->sheen);
		color_scaleby(&specular, &light->specs.point.intensity, material->specular * factor);
	}
	if (in_shadow)
	{
		color_init(&diffuse, 0.0, 0.0, 0.0);
		color_init(&specular, 0.0, 0.0, 0.0);
	}
	color_add(&return_color, &ambient, &diffuse);
	color_add(&return_color, &return_color, &specular);
	return (return_color);
}

bool	is_shadowed(t_world *world, t_vec4s *point, t_light *light)
{
	t_vec4s		v;
	t_ray		r;
	t_itx		*itx;

	lag_vec4s_sub(&v, &light->pos, point);
	ray_create(&r, point, &v);
	r.xs = intersect_world(world, &r);
	itx = get_hit(&r.xs);
	if (itx && itx->t < lag_vec4s_magnitude_ret(v))
		return (true);
	return (false);
}

t_color	reflected_color(t_world *world, t_itx_computation *comps, int depth)
{
	t_color		c;
	t_ray		r;
	t_color		reflected_color;
	t_vec4s	reflectv;
	t_vec4s	reflect_origin;
	t_vec4s	offset;

	color_init(&c, 0.0, 0.0, 0.0);
	if (depth <= 0 || comps->obj->material.reflective <= 0.0)
		return (c);
	reflectv = comps->reflectv;
	lag_vec4s_scaleby(&offset, comps->normalv, EPSILON);
	lag_vec4s_add(&reflect_origin, &comps->over_point, &offset);
	ray_create(&r, &reflect_origin, &reflectv);
	reflected_color = color_at(world, &r, depth - 1);
	color_scaleby(&reflected_color, &reflected_color, comps->obj->material.reflective);
	return (reflected_color);
}

t_color	shade_hit(t_world *world, t_itx_computation *comps, int depth)
{
	t_color		lighting_result;
	// t_color		reflection_result;
	// t_color		refraction_result;
	t_color		return_color; (void)depth;
	bool		in_shadow;
	long long	start_time, test_time;

	start_time = my_gettime();
	color_init(&return_color, 0.f, 0.f, 0.f);
	for (int i = 0; i < world->num_lights; i++)
	{
		in_shadow = is_shadowed(world, &comps->over_point, &world->lights[i]);
		lighting_result = lighting(&comps->obj->material, &world->lights[i], &comps->over_point, &comps->eyev, &comps->normalv, in_shadow);
		color_add(&return_color, &return_color, &lighting_result);
	}
	// reflection_result = reflected_color(world, comps, depth);
	// refraction_result = refracted_color(world, comps, depth);
	// if (comps->obj->material.reflective > 0.0f)
	// 	color_scaleby(&return_color, &return_color, 1.0f - comps->obj->material.reflective);
	// if (comps->obj->material.transparency > 0.0f)
	// 	color_scaleby(&return_color, &return_color, 1.0f - comps->obj->material.transparency);
	// double schlick_value = schlick(comps);
	// if (comps->obj->material.reflective > 0.0f && comps->obj->material.transparency > 0.0f)
	// {
	// 	color_scaleby(&reflection_result, &reflection_result, 1.0f - schlick_value);
	// 	color_scaleby(&reflection_result, &reflection_result, schlick_value);
	// }
	// color_add(&return_color, &return_color, &reflection_result);
	// color_add(&return_color, &return_color, &refraction_result);
	color_clamp(&return_color);
	test_time = my_gettime() - start_time;
	if (test_time > 1)
		printf("shade_hit: %lld\n", test_time);
	return (return_color);
}

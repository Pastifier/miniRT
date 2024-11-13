/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:36:57 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/03 15:37:13by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

static inline void	plane_pattern_blend(t_color *ec,
							const t_comps *comps, const t_color *intens)
{
	const t_material *mater = &comps->obj->material;
	t_vec4s	local_p;

	lag_mat4s_cross_vec4s(&comps->obj->inv_transform, &comps->over_point, &local_p);
	if ((int)(fabsf(floorf(local_p.x)) + fabsf(floorf(local_p.y)) + fabsf(floorf(local_p.z))) % 2)
		color_blend(ec, &mater->color, intens);
	else
		color_blend(ec, &mater->xordc, intens);
}

float	get_spot_light_intensity(t_light *light, t_vec4s light_v)
{
	float	cos_theta;
	float	cos_spot_angle;

	lag_vec4s_normalize(&light_v);
	cos_theta = lag_vec4s_dot_ret(&light_v, &light->specs.spot.orientation);
	cos_spot_angle = cosf(light->specs.spot.spot_angle);
	if (cos_theta >= cos_spot_angle)
		return (powf(cos_theta, SPOTLIGHT_FALLOFF));
	return (0.0f);
}

t_color	lighting(t_comps *comps, t_material *material, t_light *light, bool in_shadow)
{
	t_vec4s		light_v;
	t_vec4s		reflect_v;
	t_color		intensity;
	t_color		effective_color;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		return_color;
	float		reflect_eye_dot;
	float		light_dot_normal;
	float		factor;
	float		spot_intensity;

	if (light->type == SPOT_LIGHT)
		intensity = light->specs.spot.intensity;
	else
		intensity = light->specs.point.intensity;
	if (comps->obj->type == PLANE)
		plane_pattern_blend(&effective_color, comps, &intensity);
	else
		color_blend(&effective_color, &material->color, &intensity);
	lag_vec4s_sub(&light_v, &light->pos, &comps->over_point);
	lag_vec4s_normalize(&light_v);
	color_scaleby(&ambient, &effective_color, material->ambient);
	if (light->type == SPOT_LIGHT)
		spot_intensity = get_spot_light_intensity(light, light_v);
	else
		spot_intensity = 1.0f;
	color_scaleby(&effective_color, &effective_color, spot_intensity);
	comps->normalv.w = 0;
	lag_vec4s_dot(&light_dot_normal, &light_v, &comps->normalv);
	if (light_dot_normal < EPSILON || in_shadow)
		return (ambient);
	else
		color_scaleby(&diffuse, &effective_color, material->diffuse * light_dot_normal);
	lag_vec4s_negate(&light_v);
	reflect_v = reflect(&light_v, &comps->normalv);
	reflect_eye_dot = lag_vec4s_dot_ret(&reflect_v, &comps->eyev);
	if (reflect_eye_dot <= 0)
		color_init(&specular, 0.0, 0.0, 0.0);
	else
	{
		factor = powf(reflect_eye_dot, material->sheen);
		color_scaleby(&specular, &intensity, material->specular * factor);
	}
	color_add(&return_color, &ambient, &diffuse);
	color_add(&return_color, &return_color, &specular);
	return (return_color);
}

bool	is_shadowed(t_world *world, t_vec4s *point, t_light *light)
{
	t_vec4s		v;
	t_ray		r;
	t_itx_grp	xs;
	t_itx		*itx;
	t_vec4s		hit_pos;
	t_vec4s		hit_v;
	float		cos_theta;

	lag_vec4s_sub(&v, &light->pos, point);
	 if (light->type == SPOT_LIGHT) {
		lag_vec4s_normalize(&v);
		cos_theta = lag_vec4s_dot_ret(&v, &light->specs.spot.orientation);
		if (cos_theta < cosf(light->specs.spot.spot_angle))
			return (false);
	}
	ray_create(&r, point, &v);
	xs = intersect_world(world, &r); //
	itx = get_hit(&xs);
	if (!itx)
		return (false);
	ray_position(&hit_pos, &r, itx->t);
	lag_vec4s_sub(&hit_v, &hit_pos, point);
	if (lag_vec4s_magnitude_ret(hit_v) < lag_vec4s_magnitude_ret(v))
		return (true);
	return (false);
}

t_color	check_for_refref(t_world *world, t_comps *comps, int depth)
{
	double		schlick_value;
	t_color		reflection_result;
	t_color		refraction_result;
	t_color		return_color;

	reflection_result = reflected_color(world, comps, depth);
	refraction_result = refracted_color(world, comps, depth);
	color_init(&return_color, 0.0, 0.0, 0.0);
	if (comps->obj->material.reflective > 0.0f)
		color_scaleby(&return_color, &return_color, 1.0f - comps->obj->material.reflective);
	if (comps->obj->material.transparency > 0.0f)
		color_scaleby(&return_color, &return_color, 1.0f - comps->obj->material.transparency);
	if (comps->obj->material.reflective > 0.0f && comps->obj->material.transparency > 0.0f)
	{
		schlick_value = schlick(comps);
		color_scaleby(&reflection_result, &reflection_result, 1.0f - schlick_value);
		color_scaleby(&reflection_result, &reflection_result, schlick_value);
	}
	if (comps->obj->material.reflective > 0.0f)
		color_add(&return_color, &return_color, &reflection_result);
	if (comps->obj->material.transparency > 0.0f)
		color_add(&return_color, &return_color, &refraction_result);
	return (return_color);
}

t_color	shade_hit(t_world *world, t_comps *comps, int depth)
{
	t_color		lighting_result;
	t_color		refract_reflect;
	t_color		return_color;
	bool		in_shadow;

	color_init(&return_color, 0.f, 0.f, 0.f);
	for (int i = 0; i < world->num_lights; i++)
	{
		in_shadow = is_shadowed(world, &comps->over_point, &world->lights[i]);
		lighting_result = lighting(comps, &comps->obj->material, &world->lights[i], in_shadow);
		color_add(&return_color, &return_color, &lighting_result);
	}
	if (world->refract_reflect)
	{
		refract_reflect = check_for_refref(world, comps, depth);
		color_add(&return_color, &return_color, &refract_reflect);
	}
	color_add(&return_color, &return_color, &world->ambiance);
	color_clamp(&return_color);
	return (return_color);
}

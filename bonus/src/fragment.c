/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 07:07:39 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/31 16:59:18 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"
#include "macros.h"

static inline t_ray	ray_for_pixel(const t_camera *cam, int px, int py)
{
	t_ray		r;
	t_vec4s		pixel;
	t_vec4s		origin;
	t_vec4s		direction;

	lag_vec4sp_init(&pixel, (cam->half_width - (px + 0.5f) * cam->pixel_size),
			(cam->half_height - (py + 0.5f) * cam->pixel_size), -1);
	pixel = lag_mat4s_cross_vec4s(cam->inv_transform, pixel);
	origin = lag_vec4sp_ret(0.f, 0.f, 0.f);
	origin = lag_mat4s_cross_vec4s(cam->inv_transform, origin);
	lag_vec4s_sub(&direction, pixel, origin);
	lag_vec4s_normalize(&direction);
	ray_create(&r, &origin, &direction);
	return (r);
}

t_itx_computation prepare_computations(t_itx *itx, t_ray *r, t_itx_grp *itxs)
{
	t_itx_computation	comps;
	t_vec4s			margin;

	comps.t = itx->t;
	comps.obj = itx->object;
	ray_position(&comps.p, r, comps.t);
	comps.eyev = r->dir;
	lag_vec4s_negate(&comps.eyev);
	if (itx->object->type == SPHERE)
		comps.normalv = sphere_normal_at(itx->object, &comps.p);
	else if (itx->object->type == PLANE)
		comps.normalv = plane_normal_at(itx->object);
	else if (itx->object->type == CYLINDER)
		comps.normalv = cylinder_normal_at(itx->object, &comps.p);
	else if (itx->object->type == CUBE)
		comps.normalv = cube_normal_at(itx->object, &comps.p);
	else if (itx->object->type == CONE)
		comps.normalv = cone_normal_at(itx->object, &comps.p);
	if (lag_vec4s_dot_ret(comps.normalv, comps.eyev) < 0.f)
	{
		comps.inside = true;
		lag_vec4s_negate(&comps.normalv);
	}
	else
		comps.inside = false;
	lag_vec4s_scaleby(&margin, comps.normalv, EPSILON);
	lag_vec4s_add(&comps.over_point, comps.p, margin);
	lag_vec4s_sub(&comps.under_point, comps.p, margin);
	comps.reflectv = reflect(&r->dir, &comps.normalv);
	if (comps.obj->material.refractive_index > 0.f)
		prepare_refractions(itx, &comps, itxs);
	return (comps);
}

t_color	color_at(t_world *w, t_ray *r, int depth)
{
	t_itx_grp		world_itxs;
	t_itx			*hit;
	t_color			result;
	t_comps			comps;

	world_itxs = intersect_world(w, r);
	hit = get_hit(&world_itxs);
	if (!hit)
	{
		color_init(&result, 0.f, 0.f, 0.f);
		return (result);
	}
	comps = prepare_computations(hit, r, &world_itxs);
	return (shade_hit(w, &comps, depth));
}


t_color	rt_render_pixel(t_program *context, int x, int y)
{
	t_ray		r;
	t_color		c;

	r = ray_for_pixel(&context->cam, x, y);
	c = color_at(&context->world, &r, REFLECTION_DEPTH);
	put_pixel(&context->canvas, x, y, &c);
	return (c);
}

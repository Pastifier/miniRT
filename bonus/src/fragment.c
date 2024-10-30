/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 07:07:39 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/30 11:33:37 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colors.h"

static inline t_ray	ray_for_pixel(const t_camera *cam, int px, int py)
{
	t_ray		r;
	t_vec4s		pixel;
	t_vec4s		origin;
	t_vec4s		direction;

	lag_vec4sp_init(&pixel, (cam->half_width - (px + 0.5) * cam->pixel_size),
			(cam->half_height - (py + 0.5) * cam->pixel_size), -1);
	pixel = lag_mat4s_cross_vec4s(cam->inv_transform, pixel);
	origin = lag_vec4sp_ret(0.f, 0.f, 0.f);
	origin = lag_mat4s_cross_vec4s(cam->inv_transform, origin);
	lag_vec4s_sub(&direction, pixel, origin);
	lag_vec4s_normalize(&direction);
	ray_create(&r, &origin, &direction);
	return (r);
}

//static inline void	prepare_computations(const t_itx *hit, t_ray *r)
//{
//	t_vec4s	margin;

//	(void)hit;(void)r;(void)margin;
//}

static inline t_color	color_at(t_world *w, t_ray *r/*, int depth*/)
{
	t_itx_grp		world_itxs;
	t_itx			*hit;
	t_color			result;

	world_itxs = intersect_world(w, r);
	hit = get_hit(&world_itxs);
	if (!hit)
	{
		color_init(&result, 0.0, 0.0, 0.0);
		return (result);
	}
	//comps = prepare_computations(hit, r, &world_itxs);
	//return (shade_hit(w, &comps, depth));
		color_init(&result, 0.0, 0.0, 0.0); // temp////
	return (result); // temp////
}


t_color	rt_render_pixel(t_program *context, int x, int y)
{
	t_ray		r;
	t_color		c;

	r = ray_for_pixel(&context->cam, x, y);
	c = color_at(&context->world, &r);
	put_pixel(&context->canvas, x, y, &c);
	return (c);
}
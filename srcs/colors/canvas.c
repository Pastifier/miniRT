/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:03:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/09 17:53:46 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"
#include "objects.h"
#include "rtmath.h"
#include "macros.h"
#include <stdio.h>

t_color	color_at(t_world *w, t_ray *r)
{
	t_intersections		world_itxs;
	t_intersection		*hit;
	t_itx_computation	comps;
	t_color				result;

	world_itxs = intersect_world(w, r);
	hit = get_hit(&world_itxs);
	if (!hit)
	{
		color(&result, 0.0, 0.0, 0.0);
		return (result);
	}
	comps = prepare_computations(*hit, r);
	return (shade_hit(w, &comps));
}

void	canvas(t_program *context, int width, int height)
{
	context->canvas.ptr = mlx_new_image(context->mlx, width, height);
	// iferr: exit
	context->canvas.addr = mlx_get_data_addr(context->canvas.ptr,
		&context->canvas.bpp, &context->canvas.line_length,
			&context->canvas.endian);
	// iferr: exit
}

void	put_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	char	*dst;

	dst = canvas->addr + (y * canvas->line_length + x * (canvas->bpp / 8));
	*(uint32_t *)dst = get_color(&color);
}

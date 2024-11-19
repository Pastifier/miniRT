/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:35:38 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/19 16:36:01 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static void	fill_in_vertically(t_thread const *data, int x, int y)
{
	t_color		c_i;
	t_color		c_f;
	t_color		temp;

	c_i = fetch_pixel_color(&data->context->canvas, x, y - 1);
	if (y + _RT_SKIP_STEP - 1 >= data->context->cam.vsize)
		c_f = fetch_pixel_color(&data->context->canvas, x,
				data->context->cam.vsize - 1);
	else
		c_f = fetch_pixel_color(&data->context->canvas, x,
				y + _RT_SKIP_STEP - 1);
	if (cdiff(c_i, c_f) > _RT_LERP_THRESH)
	{
		rt_render_pixel(data->context, x, y);
		rt_render_pixel(data->context, x, y + 1);
	}
	else
	{
		temp = lerp_colors(&c_i, &c_f, 2.0f / 3.0f);
		put_pixel(&data->context->canvas, x, y, &temp);
		temp = lerp_colors(&c_i, &c_f, 1.0f / 3.0f);
		put_pixel(&data->context->canvas, x, y + 1, &temp);
	}
}

static void	check_vertical_fill(t_thread const *data, int x, int y)
{
	t_program		*context;
	t_camera		*cam;
	t_color			temp;

	context = data->context;
	cam = &context->cam;
	if (y + (_RT_SKIP_STEP - 1) < cam->vsize)
		fill_in_vertically(data, x, y);
	else
	{
		temp = fetch_pixel_color(&context->canvas, x, y - 1);
		if (y < cam->vsize)
			put_pixel(&context->canvas, x, y, &temp);
		temp = fetch_pixel_color(&context->canvas, x, y);
		if (y + 1 < cam->vsize)
			put_pixel(&context->canvas, x, y + 1, &temp);
	}
}

void	interpolate_vertical(t_thread const *data)
{
	t_program		*context;
	t_camera		*cam;
	int				x;
	int				y;
	int				y_f;

	context = data->context;
	cam = &context->cam;
	y_f = data->y_f;
	y = data->y + 1;
	while (y < y_f)
	{
		x = 1;
		while (x < cam->hsize)
		{
			check_vertical_fill(data, x, y);
			x++;
		}
		y += _RT_SKIP_STEP;
	}
}

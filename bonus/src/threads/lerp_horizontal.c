/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lerp_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:11:01 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/19 16:36:05 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

static void	fill_in_horizontal(t_thread const *data, int x, int y)
{
	t_color		c_i;
	t_color		c_f;
	t_color		temp;

	c_i = fetch_pixel_color(&data->context->canvas, x - 1, y);
	c_f = fetch_pixel_color(&data->context->canvas, x + _RT_SKIP_STEP - 1, y);
	if (cdiff(c_i, c_f) > _RT_LERP_THRESH)
	{
		rt_render_pixel(data->context, x, y);
		rt_render_pixel(data->context, x + 1, y);
	}
	else
	{
		temp = lerp_colors(&c_i, &c_f, 2.0f / 3.0f);
		put_pixel(&data->context->canvas, x, y, &temp);
		temp = lerp_colors(&c_i, &c_f, 1.0f / 3.0f);
		put_pixel(&data->context->canvas, x + 1, y, &temp);
	}
}

static void	check_horizontal_fill(t_thread const *data, int x, int y)
{
	t_program	*context;
	t_camera	*cam;
	t_color		temp;

	context = data->context;
	cam = &context->cam;
	if (x + (_RT_SKIP_STEP - 1) < cam->hsize)
		fill_in_horizontal(data, x, y);
	else
	{
		temp = fetch_pixel_color(&context->canvas, x - 1, y);
		if (x < cam->hsize)
			put_pixel(&context->canvas, x, y, &temp);
		temp = fetch_pixel_color(&context->canvas, x, y);
		if (x + 1 < cam->hsize)
			put_pixel(&context->canvas, x + 1, y, &temp);
	}
}

void	interpolate_horizontal(t_thread const *data)
{
	t_program	*context;
	t_camera	*cam;
	int			x;
	int			y;
	int			y_f;

	context = data->context;
	cam = &context->cam;
	y = data->y;
	y_f = data->y_f;
	while (y < y_f)
	{
		x = 1;
		while (x < cam->hsize)
		{
			check_horizontal_fill(data, x, y);
			x += _RT_SKIP_STEP;
		}
		y++;
	}
}

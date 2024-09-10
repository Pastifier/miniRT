/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:48:22 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/09 23:45:11 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "colors.h"
#include "rtmath.h"
#include "minirt.h"
#include "macros.h"
#include "libft.h"
#include <stdio.h>

static void	fill_in_horizontal(t_thread_data *data, int x, int y)
{
	t_color		c_i;
	t_color		c_f;

	c_i = get_pixel_color(&data->context->canvas, x - 1, y);
	c_f = get_pixel_color(&data->context->canvas, x + SKIPPED_PIX - 1, y);
	if (cdiff(c_i, c_f) > THRESHOLD)
	{
		// super_sample_pix(data, x - 1, y);
		//super_sample_pix(data, x, y);
		//super_sample_pix(data, x + 1, y);
		// super_sample_pix(data, x + 2, y);
		return ;
	}
	else
	{
		put_pixel(&data->context->canvas, x, y, lerp(c_i, c_f, 2.0 / 3.0));
		put_pixel(&data->context->canvas, x, y, lerp(c_i, c_f, 1.0 / 3.0));
	}
}

static void	fill_in_vertically(t_thread_data *data, int x, int y)
{
	t_color		c_i;
	t_color		c_f;

	c_i = get_pixel_color(&data->context->canvas, x, y - 1);
	if (y + SKIPPED_PIX - 1 >= data->y_f && y < data->y_f)
		super_sample_pix(data, x, y);
	if (y + SKIPPED_PIX - 1 >= data->y_f && y + 1 < data->y_f)
		super_sample_pix(data, x, y + 1);
	if (y + SKIPPED_PIX - 1 >= data->y_f)
		return ;
	c_f = get_pixel_color(&data->context->canvas, x, y + SKIPPED_PIX - 1);
	if (cdiff(c_i, c_f) > THRESHOLD)
	{
		//// super_sample_pix(data, x, y - 1);
		//super_sample_pix(data, x, y);
		//super_sample_pix(data, x, y + 1);
		//// super_sample_pix(data, x, y + 2);
		return ;
	}
	else
	{
		put_pixel(&data->context->canvas, x, y, lerp(c_i, c_f, 2.0 / 3.0));
		put_pixel(&data->context->canvas, x, y, lerp(c_i, c_f, 1.0 / 3.0));
	}
}

void	interpolate_horizontal(t_thread_data *data)
{
	t_program		*context = data->context;
	t_camera		*cam = &context->camera;
	int				x;
	int				y;
	int				y_f;

	y = data->id * (cam->vsize / THREAD_NUM);
	y_f = data->y_f;
	while (y < y_f)
	{
		x = 1;
		while(x < cam->hsize)
		{
			if (x + (SKIPPED_PIX - 1) < cam->hsize)
			{
				fill_in_horizontal(data, x, y);
			}
			else
			{
				if (x < cam->hsize)
					put_pixel(&context->canvas, x, y, get_pixel_color(&context->canvas, x - 1, y));
				if (x + 1 < cam->hsize)
					put_pixel(&context->canvas, x + 1, y, get_pixel_color(&context->canvas, x, y));
			}
			x += SKIPPED_PIX;
		}
		y++;
	}
}

void	interpolate_vertical(t_thread_data *data)
{
	t_program		*context = data->context;
	t_camera		*cam = &context->camera;
	int				x;
	int				y;
	int				y_f;

	y_f = data->y_f;
	y = data->y;
	while (y < y_f)
	{
		x = 1;
		while (x < cam->hsize)
		{
			if (y + (SKIPPED_PIX - 1) < cam->vsize)
			{
				fill_in_vertically(data, x, y);
			}
			else
			{
				if (y < cam->vsize)
					put_pixel(&context->canvas, x, y, get_pixel_color(&context->canvas, x, y - 1));
				if (y + 1 < cam->vsize)
					put_pixel(&context->canvas, x, y + 1, get_pixel_color(&context->canvas, x, y));
			}
			x++;
		}
		y += SKIPPED_PIX;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:59 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/06 19:34:59 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "macros.h"
#include "mlx.h"
#include <stdlib.h>

/*

	Assuming id is not zero-indexed.
	for (int y = (id - 1) * (vsize / THREAD_NUM) + (id - 1 != 0);
		y < id * (vsize / THREAD_NUM); y++)
	{
		for (int x = 0; x < hsize; x++)
		{
			
		}
	}

*/

t_color	get_pixel_color(t_canvas *canvas, int x, int y)
{
	char		*src;
	uint32_t	color_value;
	t_color		color;

	src = canvas->addr + (y * canvas->line_length + x * (canvas->bpp / 8));
	color_value = *(uint32_t *)src;
	color.set.x = (color_value >> 16) & 0xFF;
	color.set.y = (color_value >> 8) & 0xFF;
	color.set.z = color_value & 0xFF;
	return (color);
}

t_color	lerp(t_color a, t_color b, double t)
{
	t_color	ret;

	ret.r = (a.r * (1.0 - t)) + (b.r * t);
	ret.g = (a.g * (1.0 - t)) + (b.g * t);
	ret.b = (a.b * (1.0 - t)) + (b.b * t);
	return (ret);
}

// Hard-coded for now...
void	interpolate_horizontally(t_canvas *canvas, t_webcam *cam)
{
	t_color left;
	t_color closest_right;
	t_color interp;

	for (int y = 0; y < cam->vsize; y += SKIPPED_PIXELS)
	{
		for (int x = 1; x < cam->hsize - SKIPPED_PIXELS; x += SKIPPED_PIXELS)
		{
			// for (int i = 1; i < SKIPPED_PIXELS; i++)
			//{
			//	t_color left = get_pixel_color(canvas, x - i, y);
			//	t_color closest_right = get_pixel_color(canvas, x + SKIPPED_PIXELS - i, y);
			//	double t = i / (double)(SKIPPED_PIXELS);
			//	t_color interpolated = lerp(left, closest_right, t);
			//	put_pixel(canvas, x + i, y, &interpolated);
			// }
			left = get_pixel_color(canvas, x - 1, y);
			closest_right = get_pixel_color(canvas, x + SKIPPED_PIXELS - 1, y);
			interp = lerp(left, closest_right, 1.0f /*(2.0f * (x - 1) + SKIPPED_PIXELS)*/ / (double)SKIPPED_PIXELS);
			put_pixel(canvas, x, y, &interp);
			//left = get_pixel_color(canvas, x, y);
			//interp = lerp(left, closest_right, (2.0f * x + (SKIPPED_PIXELS - 1) / (double)SKIPPED_PIXELS));
			//put_pixel(canvas, x + 1, y, &interp);
			//left = closest_right;
		}
		// idea#1: get starting x, get ending x, and collapse...
	}
}

void	interpolate_horizontally_threads(t_canvas *canvas, t_webcam *cam, int y_i, int y_f)
{
	t_color left;
	t_color closest_right;
	t_color interp;

	for (int y = y_i; y < y_f; y += SKIPPED_PIXELS)
	{
		for (int x = 1; x < cam->hsize - SKIPPED_PIXELS; x += SKIPPED_PIXELS)
		{
			// for (int i = 1; i < SKIPPED_PIXELS; i++)
			//{
			//	t_color left = get_pixel_color(canvas, x - i, y);
			//	t_color closest_right = get_pixel_color(canvas, x + SKIPPED_PIXELS - i, y);
			//	double t = i / (double)(SKIPPED_PIXELS);
			//	t_color interpolated = lerp(left, closest_right, t);
			//	put_pixel(canvas, x + i, y, &interpolated);
			// }
			left = get_pixel_color(canvas, x - 1, y);
			closest_right = get_pixel_color(canvas, x + SKIPPED_PIXELS - 1, y);
			interp = lerp(left, closest_right, 1.0f /*(2.0f * (x - 1) + SKIPPED_PIXELS)*/ / (double)SKIPPED_PIXELS);
			put_pixel(canvas, x, y, &interp);
			//left = get_pixel_color(canvas, x, y);
			//interp = lerp(left, closest_right, (2.0f * x + (SKIPPED_PIXELS - 1) / (double)SKIPPED_PIXELS));
			//put_pixel(canvas, x + 1, y, &interp);
			//left = closest_right;
		}
		// idea#1: get starting x, get ending x, and collapse...
	}
}

void	interpolate_vertically(t_canvas *canvas, t_webcam *cam)
{
	t_color top;
	t_color closest_bottom;
	t_color interp;

	for (int x = 0; x < cam->hsize; x += SKIPPED_PIXELS)
	{
		for (int y = 1; y < cam->vsize - SKIPPED_PIXELS; y += SKIPPED_PIXELS)
		{
			//for (int i = 1; i < SKIPPED_PIXELS; i++)
			//{
			//	t_color top = get_pixel_color(canvas, x, y + i);
			//	t_color closest_bottom = get_pixel_color(canvas, x, y + SKIPPED_PIXELS - i);
			//	double t = i / (double)(SKIPPED_PIXELS);
			//	t_color interpolated = lerp(top, closest_bottom, t);
			//	put_pixel(canvas, x, y + i, &interpolated);
			//}
			top = get_pixel_color(canvas, x, y - 1);
			closest_bottom = get_pixel_color(canvas, x, y + SKIPPED_PIXELS - 1);
			interp = lerp(top, closest_bottom, 1.0f /*(2.0f * (x - 1) + SKIPPED_PIXELS)*/ / (double)SKIPPED_PIXELS);
			put_pixel(canvas, x, y, &interp);
		}
	}
}


void	*render_with_threads(void *thread_)
{
	t_ray		r;
	t_thread	*ptcontext;
	t_webcam	cam;
	int			y_i;
	int			y_f;

	ptcontext = (t_thread*)thread_;
	cam = ptcontext->world->cam;
	y_i = (ptcontext->id * cam.vsize / THREAD_NUM);
	y_f = (ptcontext->id + 1) * cam.vsize / THREAD_NUM;
	for (int y = y_i; y < y_f; y++/*= SKIPPED_PIXELS*/)
	{
		for (int x = 0; x < cam.hsize; x++/*= SKIPPED_PIXELS*/)
		{
			r = to_the_pixel_and_beyond(&cam, x, y);
			r.c = color_at(ptcontext->world, &r);
			put_pixel(&ptcontext->context->canvas, x, y, &r.c);
		}
	}
	//interpolate_horizontally_threads(&ptcontext->context->canvas,
	//		&ptcontext->world->cam, y_i, y_f);
	return (thread_);
}
#include <stdio.h>

t_thread	*init_threads(t_program *context, t_world *world)
{
	t_thread	*threads;
	t_canvas	*canvas;
	int			id;

	threads = malloc(sizeof(t_thread) * THREAD_NUM);
	if (!threads)
		return (NULL);
	id = -1;
	while (++id < THREAD_NUM)
	{
		threads[id].id = id;
		threads[id].world = world;
		threads[id].context = context;
		// guard this, I guess...
		pthread_create(&threads[id].thread, NULL, render_with_threads,
			&threads[id]);
	}
	canvas = &context->canvas;
	while (--id >= 0)
		pthread_join(threads[id].thread, NULL);
	//interpolate_horizontally(canvas, &world->cam);
	//interpolate_vertically(canvas, &world->cam);
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr,
			0, 0);
	return (threads);
}

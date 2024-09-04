/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:09:59 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/04 22:00:34 by ebinjama         ###   ########.fr       */
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
	for (int y = y_i; y < y_f; y+=3)
	{
		for (int x = 0; x < cam.hsize; x+=3)
		{
			r = to_the_pixel_and_beyond(&cam, x, y);
			r.c = color_at(ptcontext->world, &r);
			put_pixel(&ptcontext->context->canvas, x, y, &r.c);
		}
	}
	return (thread_);
}

t_thread	*init_threads(t_program *context, t_world *world)
{
	t_thread	*threads;
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
	while (--id >= 0)
		pthread_join(threads[id].thread, NULL);
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr,
			0, 0);
	return (threads);
}

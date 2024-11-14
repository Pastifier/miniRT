/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:47:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/08 22:02:07 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/time.h>

extern void	*render_row(void *param); //
//extern void	*lerp_routine(void *param); //

long long	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return ((void)write(2, "Error.\n", 8), -1);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

void	*thread_arbiter(void *arg)
{
	t_thread	*data = (t_thread *)arg;

	while (true)
	{
		pthread_mutex_lock(&data->mutex);
		while (!data->context->stop && !data->work_ready)
			pthread_cond_wait(&data->cond, &data->mutex);
		if (data->context->stop)
		{
			pthread_mutex_unlock(&data->mutex);
			break ;
		}
		pthread_mutex_unlock(&data->mutex);
		render_row(data);
		pthread_mutex_lock(&data->mutex);
		data->work_ready = false;
		pthread_mutex_unlock(&data->mutex);
	}
	return (NULL);
}

bool	pool_init(t_program *context)
{
	t_thread	*thread;

	context->pool = malloc(sizeof(t_thread) * _RT_NUM_THREADS);
	if (!context->pool)
		return (false);
	for (int i = 0; i < _RT_NUM_THREADS; i++)
	{
		thread = &context->pool[i];
		thread->context = context;
		thread->id = i;
		thread->y = i * (context->cam.vsize / _RT_NUM_THREADS);
		thread->y_f = (i + 1) * (context->cam.vsize / _RT_NUM_THREADS);
		pthread_mutex_init(&thread->mutex, NULL);
		pthread_cond_init(&thread->cond, NULL);
		thread->work_ready = false;
		pthread_create(&thread->thread, NULL, thread_arbiter, thread);
	}
	return (true);
}

void pool_start_frame(t_program *context)
{
	t_thread	*thread;

	for (int i = 0; i < _RT_NUM_THREADS; i++)
	{
		thread = &context->pool[i];
		pthread_mutex_lock(&thread->mutex);
		thread->work_ready = true;
		pthread_cond_signal(&thread->cond);
		pthread_mutex_unlock(&thread->mutex);
	}
}

void pool_wait_for_frame(t_program *context)
{
	t_thread	*thread;

	for (int i = 0; i < _RT_NUM_THREADS; i++)
	{
		thread = &context->pool[i];
		pthread_mutex_lock(&thread->mutex);
		while (thread->work_ready)
		{
			pthread_mutex_unlock(&thread->mutex); // Avoid deadlock
			pthread_mutex_lock(&thread->mutex);	  // Re-check lock
		}
		pthread_mutex_unlock(&thread->mutex);
	}
}

bool	pool_init_join(t_program *context)
{
	// t_thread	*new_pool;
	long long start_time, frame_time;
	//int y;

	start_time = my_gettime();
	// y = -1;
	// context->pool = malloc(sizeof(t_thread) * _RT_NUM_THREADS);//context->pool;
	// new_pool = context->pool;
	// while (++y < _RT_NUM_THREADS && new_pool)
	//{
	//	new_pool[y].id = y;
	//	new_pool[y].context = context;
	//	new_pool[y].y = y * (context->cam.vsize / _RT_NUM_THREADS);
	//	new_pool[y].y_f = (y + 1) * (context->cam.vsize / _RT_NUM_THREADS);
	//	new_pool[y].x = y * (context->cam.hsize / _RT_NUM_THREADS);
	//	new_pool[y].x_f = (y + 1) * (context->cam.hsize / _RT_NUM_THREADS);
	//	pthread_create(&new_pool[y].thread, NULL, render_row, &new_pool[y]);
	// }
	// while (y-- && new_pool)
	//	pthread_join(new_pool[y].thread, NULL);
	// if (context->pool)
	//{
	//	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
	//	free(context->pool);
	//	context->pool = NULL;
	// }
	//  Start work on the frame
	pool_start_frame(context);
	// Wait for all threads to finish
	pool_wait_for_frame(context);

	// Display the rendered frame
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
	frame_time = my_gettime() - start_time;
	printf("Frame took: %lld\n", frame_time);
	return (true);
}

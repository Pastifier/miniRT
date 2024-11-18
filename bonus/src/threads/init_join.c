/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:47:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 16:13:44 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/time.h>

extern void	*render_row(void *param);

long long	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return ((void)write(2, "Error.\n", 8), -1);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

bool	pool_init(t_program *context)
{
	t_thread	*thread;
	int			i;

	context->pool = malloc(sizeof(t_thread) * _RT_NUM_THREADS);
	if (!context->pool)
		return (false);
	i = -1;
	while (++i < _RT_NUM_THREADS)
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

void	pool_start_frame(t_program *context)
{
	t_thread	*thread;
	int			i;

	i = -1;
	while (++i < _RT_NUM_THREADS)
	{
		thread = &context->pool[i];
		pthread_mutex_lock(&thread->mutex);
		thread->work_ready = true;
		pthread_cond_signal(&thread->cond);
		pthread_mutex_unlock(&thread->mutex);
	}
}

void	pool_wait_for_frame(t_program *context)
{
	t_thread	*thread;
	int			i;

	i = -1;
	while (++i < _RT_NUM_THREADS)
	{
		thread = &context->pool[i];
		pthread_mutex_lock(&thread->mutex);
		while (thread->work_ready)
		{
			pthread_mutex_unlock(&thread->mutex);
			pthread_mutex_lock(&thread->mutex);
		}
		pthread_mutex_unlock(&thread->mutex);
	}
}

bool	pool_init_join(t_program *context)
{
	long long	start_time;
	long long	frame_time;

	start_time = my_gettime();
	pool_start_frame(context);
	pool_wait_for_frame(context);
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr,
		0, 0);
	frame_time = my_gettime() - start_time;
	printf("Frame took: %lld\n", frame_time);
	return (true);
}

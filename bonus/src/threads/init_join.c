/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:47:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 21:13:53 by ebinjama         ###   ########.fr       */
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

bool	pool_init_join(t_program *context)
{
	t_thread	*new_pool;
	long long	start_time, frame_time;
	int			y;

	start_time = my_gettime();
	y = -1;
	new_pool = malloc(sizeof(t_thread) * _RT_NUM_THREADS);//context->pool;
	while (++y < _RT_NUM_THREADS)
	{
		new_pool[y].id = y;
		new_pool[y].context = context;
		new_pool[y].y = y * (context->cam.vsize / _RT_NUM_THREADS);
		new_pool[y].y_f = (y + 1) * (context->cam.vsize / _RT_NUM_THREADS);
		new_pool[y].x = y * (context->cam.hsize / _RT_NUM_THREADS);
		new_pool[y].x_f = (y + 1) * (context->cam.hsize / _RT_NUM_THREADS);
		pthread_create(&new_pool[y].thread, NULL, render_row, &new_pool[y]);
	}
	while (y--)
		pthread_join(new_pool[y].thread, NULL);
	//if (context->pool)
	//{
	//	free(context->pool);
	//	context->pool = NULL;
	//}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
	free(new_pool);
	frame_time = my_gettime() - start_time;
	printf("Frame took: %lld\n", frame_time);
	return (true);
}

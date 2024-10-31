/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:47:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/31 22:39:25 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "mlx.h"
#include <stdio.h>

extern void	*render_row(void *param); //
//extern void	*lerp_routine(void *param); //

bool	pool_init_join(t_program *context)
{
	t_thread	*new_pool;
	int			y;

	y = -1;
	new_pool = context->pool;
	while (++y < _RT_NUM_THREADS && new_pool)
	{
		new_pool[y].id = y;
		new_pool[y].context = context;
		new_pool[y].y = y * (context->cam.vsize / _RT_NUM_THREADS);
		new_pool[y].y_f = (y + 1) * (context->cam.vsize / _RT_NUM_THREADS);
		new_pool[y].x = y * (context->cam.hsize / _RT_NUM_THREADS);
		new_pool[y].x_f = (y + 1) * (context->cam.hsize / _RT_NUM_THREADS);
		pthread_create(&new_pool[y].thread, NULL, render_row, &new_pool[y]);
	}
	while (y-- && new_pool)
		pthread_join(new_pool[y].thread, NULL);
	if (context->pool)
	{
		free(context->pool);
		context->pool = NULL;
	}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr, 0, 0);
	printf("Done rendering\n");
	return (true);
}

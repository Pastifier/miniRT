/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:47:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/27 06:59:01 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

extern void	*render_row(void *param); //
//extern void	*lerp_routine(void *param); //

bool	pool_init_join(t_program *context)
{
	t_thread	*new_pool;
	int			y;

	new_pool = malloc(sizeof(t_thread) * _RT_NUM_THREADS);
	if (!new_pool && (context->pool = new_pool, false))
		return (false);
	y = -1;
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
	//y = -1;
	//while (++y < _RT_NUM_THREADS)
	//	pthread_create(&new_pool[y].thread, NULL, lerp_routine, &new_pool[y]);
	//while (y--)
	//	pthread_join(new_pool[y].thread, NULL);
	return (free(new_pool), true);
}

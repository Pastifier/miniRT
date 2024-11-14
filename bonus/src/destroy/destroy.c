/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:06:16 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 09:26:22 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"
#include "macros.h"

void	destroy_mlx(t_program *context)
{
	mlx_destroy_image(context->mlx, context->canvas.ptr);
	mlx_destroy_window(context->mlx, context->win);
	free(context->mlx);
}

void	destroy_world(t_program *context)
{
	free(context->world.lights);
	free(context->world.shapes);
}

int	destroy_program(t_program *context)
{
	//if (context->pool)
	//{
	//	for (int i = 0; i < _RT_NUM_THREADS; i++)
	//		pthread_cancel(context->pool[i].thread);
	//	free(context->pool);
	//	context->pool = NULL;
	//}
	if (context->pool)
	{
		context->stop = true;
		for (int i = 0; i < _RT_NUM_THREADS; i++)
		{
			pthread_mutex_lock(&context->pool[i].mutex);
			pthread_cond_signal(&context->pool[i].cond);
			pthread_mutex_unlock(&context->pool[i].mutex);
		}
		for (int i = 0; i < _RT_NUM_THREADS; i++)
			pthread_join(context->pool[i].thread, NULL);
		free(context->pool);
		context->pool = NULL;
	}
	destroy_world(context);
	destroy_mlx(context);
	return (exit(0), 0);
}

// @warning Assumes `arr` is `NULL`-terminated.
void	str_arr_destroy(char **arr)
{
	char	**original;

	if (!arr)
		return ;
	original = arr;
	while (*arr)
		free(*arr++);
	free(original);
}

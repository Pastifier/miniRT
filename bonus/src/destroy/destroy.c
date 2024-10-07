/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 06:06:16 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 06:08:33 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"

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

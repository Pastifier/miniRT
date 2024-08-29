/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:03:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 20:07:59 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

void	canvas(t_program *context, int width, int height)
{
	context->canvas.ptr = mlx_new_image(context->mlx, width, height);
	// iferr: exit
	context->canvas.addr = mlx_get_data_addr(context->canvas.ptr,
		&context->canvas.bpp, &context->canvas.line_length,
			&context->canvas.endian);
	// iferr: exit
}

void	put_pixel(t_canvas *canvas, int x, int y, t_color *color)
{
	char	*dst;

	dst = canvas->addr + (y * canvas->line_length + x * (canvas->bpp / 8));
	*(uint32_t *)dst = get_color(color);
}

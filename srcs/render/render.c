/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 22:16:09 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 22:36:48by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "render.h"

void	render(t_webcam *cam, t_world *world, t_program *context)
{
	t_ray	r;

	for (int y = 0; y < cam->vsize - 1; y++)
	{
		for (int x = 0; x < cam->hsize - 1; x++)
		{
			r = to_the_pixel_and_beyond(cam, x, y);
			r.c = color_at(world, &r);
			put_pixel(&context->canvas, x, y, &r.c);
		}
	}
	mlx_put_image_to_window(context->mlx, context->win,
		context->canvas.ptr, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:48:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/09 15:48:41 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "colors.h"
#include "rtmath.h"
#include "minirt.h"
#include "macros.h"
#include "libft.h"

t_color	super_sample_pix(t_thread_data *data, double x, double y)
{
	t_ray			r;
	t_color		color;
	t_color		avg_color;
	int			i;
	int			j;

	ft_bzero(&color, sizeof(t_color));
	color = render_pixel(data->context, x, y);
	cadd(&avg_color, &avg_color, &color);
	i = -1;
	while (++i < SKIPPED_PIX - 1)
	{
		j = -1;
		while (++j < SKIPPED_PIX - 1)
		{
			r = ray_for_pixel(&data->context->camera,
			x + (i + 0.5) / (SKIPPED_PIX - 1),
			y + (j + 0.5) / (SKIPPED_PIX - 1));
			color = color_at(&data->context->world, &r);
			cadd(&avg_color, &avg_color, &color);
		}
	}
	cscale(&avg_color, &avg_color, 1.0 / 5);
	cclamp(&avg_color);
	put_pixel(&data->context->canvas, x, y, avg_color);
	return (avg_color);
}

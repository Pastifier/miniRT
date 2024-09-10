/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 14:48:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/10 16:03:32 by ebinjama         ###   ########.fr       */
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
			color = render_pixel(data->context,
			x + (i + 0.5) / (SKIPPED_PIX - 1),
			y + (j + 0.5) / (SKIPPED_PIX - 1));
			cadd(&avg_color, &avg_color, &color);
		}
	}
	cscale(&avg_color, &avg_color, 1.0 / 5.0);
	cclamp(&avg_color);
	put_pixel(&data->context->canvas, x, y, avg_color);
	return (avg_color);
}

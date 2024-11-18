/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:31:02 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 15:56:54 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

void	*render_row(void *arg)
{
	const t_thread		*data = (t_thread *)arg;
	t_camera			*cam;
	int					x;
	int					y;
	int					y_f;

	y = data->y;
	y_f = data->y_f;
	cam = &data->context->cam;
	while (y < y_f)
	{
		x = 0;
		while (x < cam->hsize)
		{
			rt_render_pixel(data->context, x, y);
			x += _RT_SKIP_STEP;
		}
		y += _RT_SKIP_STEP;
	}
	interpolate_horizontal(data);
	interpolate_vertical(data);
	return (NULL);
}

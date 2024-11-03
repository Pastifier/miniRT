/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:31:02 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/02 20:03:45 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

void	*render_row(void *arg)
{
	t_thread		*data = (t_thread *)arg;
	t_program		*context = data->context;
	t_camera		*cam = &context->cam;
	int				x;
	int				y;
	int				y_f;

	y = data->y;
	y_f = data->y_f;
	while (y < y_f)
	{
		x = 0;
		while(x < cam->hsize)
		{
			rt_render_pixel(context, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

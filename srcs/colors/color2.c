/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:08:30 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/10 16:04:04 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "macros.h"
#include "render.h"

void	cclamp(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	else if (color->r < 0)
		color->r = 0;
	if (color->g > 1)
		color->g = 1;
	else if (color->g < 0)
		color->g = 0;
	if (color->b > 1)
		color->b = 1;
	else if (color->b < 0)
		color->b = 0;
}

uint32_t	get_color(t_color *color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	color_value;

	cclamp(color);
	r = (uint32_t)(color->r * 255.999);
	g = (uint32_t)(color->g * 255.999);
	b = (uint32_t)(color->b * 255.999);
	color_value = 0xFF000000;
	if (OS_MACOS)
		color_value = 0x00000000;
	return (color_value | r << 16 | g << 8 | b);
}

#include <stdio.h>
#include "pthread.h"

t_color	get_pixel_color(t_canvas *canvas, int x, int y)
{
	char		*src;
	uint32_t	color_value;
	t_color		color;

	src = canvas->addr + (y * canvas->line_length + x * (canvas->bpp / 8));
	color_value = *(uint32_t *)src;
	color.set.x = (color_value >> 16) & 0xFF;
	color.set.y = (color_value >> 8) & 0xFF;
	color.set.z = color_value & 0xFF;
	return (color);
}

t_color	lerp(t_color a, t_color b, double t)
{
	t_color	ret;

	ret.r = (b.r * t) + (a.r * (1.0 - t));
	ret.g = (b.g * t) + (a.g * (1.0 - t));
	ret.b = (b.b * t) + (a.b * (1.0 - t));
	return (ret);
}

int	cdiff(t_color a, t_color b)
{
	int				r_diff;
	int				g_diff;
	int				b_diff;

	r_diff = fabs((a.r * 255.999) - (b.r * 255.999));
	g_diff = fabs((a.g * 255.999) - (b.g * 255.999));
	b_diff = fabs((a.b * 255.999) - (b.b * 255.999));
	return (r_diff + g_diff + b_diff);
}

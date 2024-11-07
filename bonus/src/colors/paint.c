/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 01:37:10 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 02:43:49 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "miniRT.h"
#include "macros.h"

void	color_init(t_color *target, float r, float g, float b)
{
	target->v = lag_vec4s_ret((_RT_OS_MACOS_ == 0), r, g, b);
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

void	color_clamp(t_color *color)
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

uint32_t	get_color32(const t_color *_color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	color_value;
	t_color		color;

	color = *_color;
	color_clamp(&color);
	r = (uint32_t)(color.r * 255.999);
	g = (uint32_t)(color.g * 255.999);
	b = (uint32_t)(color.b * 255.999);
	color_value = 0xFF000000 * (_RT_OS_MACOS_ == 0);
	return (color_value | r << 16 | g << 8 | b);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:08:30 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 05:08:10 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "macros.h"

void	clamp(t_color *color)
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

	clamp(color);
	r = (uint32_t)(color->r * 255.999);
	g = (uint32_t)(color->g * 255.999);
	b = (uint32_t)(color->b * 255.999);
	color_value = 0xFF000000;
	if (OS_MACOS)
		color_value = 0x00000000;
	return (color_value | r << 16 | g << 8 | b);
}

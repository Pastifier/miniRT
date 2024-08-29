/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:08:30 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 00:16:28 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "macros.h"

uint32_t	get_color(t_color *color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	color_value;

	r = (uint32_t)(color->r * 255.999);
	g = (uint32_t)(color->g * 255.999);
	b = (uint32_t)(color->b * 255.999);
	color_value = 0xFF000000;
	if (OS_MACOS)
		color_value = 0x00000000;
	return (color_value | r << 16 | g << 8 | b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:00:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/27 01:18:09 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minirt.h"
#include "vectors.h"
#include "ray.h"
#include "log.h"

uint32_t	assign_color(uint8_t r,uint8_t g, uint8_t b)
{
	uint32_t	ret;

	ret = 0xFF;
	if (OS_IS_MAC)
		ret = 0x00;
	ret |= (r << 16);
	ret |= (g << 8);
	ret |= b;
	return (ret);
}

void	pixel_put(t_data *data, t_vector2 point, int color)
{
	char	*dst;

	dst = data->addr + ((int)point.y * data->line_length
			+ (int)point.x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}
*/

uint32_t	ray_color(t_ray ray)
{
	double		a;
	t_vector3	normal;

	normal = vec3_normal(ray.dir);
	a = 0.5 * (normal.y + 1.0);
	return (assign_color(0xFF * (1 - a) , 0xFF * (1 - a), 0xFF * (1 - a))
			+ assign_color(0x0F * a, 0xF0 * a, 0xFF * a));
}

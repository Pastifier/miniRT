/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:00:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 16:28:43 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
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

//Temp for testing spheres
static bool	hit_sphere(t_vector3 center, double radius, t_ray *ray)
{
	t_vector3	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = vec3_subtract(center, ray->origin);
	a = vec3_dot(ray->dir, ray->dir);
	b = -2.0 * vec3_dot(ray->dir, oc);
	c = vec3_dot(oc, oc) - (radius * radius);
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

uint32_t	ray_color(t_ray *ray)
{
	t_vector3	unit_dir;
	double		t;

	//Temp for testing spheres
	if (hit_sphere((t_vector3){0, 0, -1}, 0.5, ray))
		return (assign_color(255, 0, 0));

	unit_dir = vec3_normal(ray->dir);
	t = 0.5 * (unit_dir.y + 1.0);
	return (assign_color(128 * (t), 178 * (t), 255 * (t))
		+ assign_color(255 * (1.0-t), 255 * (1.0-t), 255 * (1.0-t)));
}

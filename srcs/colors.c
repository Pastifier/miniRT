/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:00:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/27 01:36:03 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minirt.h"
#include "vectors.h"
#include "ray.h"
#include "log.h"
#include <stdbool.h>

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
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
*/

bool	hit_sphere(t_vector3 center, double radius, t_ray ray)
{
	t_vector3	distance_to_center;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	distance_to_center = vec3_subtract(center, ray.origin);
	a = vec3_dot(ray.dir, ray.dir);
	b = -2.0 * vec3_dot(ray.dir, distance_to_center);
	c = vec3_dot(distance_to_center, distance_to_center) - (radius * radius);
	discriminant = (b * b) - (4 * a * c);
	return (discriminant >= 0);
}

uint32_t	ray_color(t_ray ray)
{
	double		a;
	t_vector3	normal;

	if (hit_sphere((t_vector3){0, 0, -1}, 0.5, ray))
		return (assign_color(0xFF, 0x0, 0x0));
	normal = vec3_normal(ray.dir);
	a = 0.5 * (normal.y + 1.0);
	return (assign_color(0xFF * (1 - a) , 0xFF * (1 - a), 0xFF * (1 - a))
			+ assign_color(0xFF * 0.5 * a, 0xFF * 0.7 * a, 0xFF * a));
}

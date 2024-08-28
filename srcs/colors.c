/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:00:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 11:45:31 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minirt.h"
#include "vectors.h"
#include "ray.h"
#include "log.h"
#include <math.h>
#include "utils.h"

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

uint32_t	convert_to_color(float r, float g, float b)
{
	r = clamp(r, 0.0f, 1.0f);
	g = clamp(g, 0.0f, 1.0f);
	b = clamp(b, 0.0f, 1.0f);
	uint8_t red = (uint8_t)(r * 255.0f);
	uint8_t green = (uint8_t)(g * 255.0f);
	uint8_t blue = (uint8_t)(b * 255.0f);
	uint32_t rgb = (red << 16) | (green << 8) | blue;
	if (!OS_IS_MAC)
		rgb |= (0xFF << 32);
	return rgb;
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

double	hit_sphere(t_vector3 center, double radius, t_ray ray)
{
	t_vector3	distance_to_center;
	double		a;
	double		h;
	double		c;
	double		discriminant;

	distance_to_center = vec3_subtract(center, ray.origin);
	a = vec3_magnitude_sqrd(ray.dir);
	h = vec3_dot(ray.dir, distance_to_center);
	c = vec3_magnitude_sqrd(distance_to_center) - (radius * radius);
	discriminant = (h * h) - (a * c);
	if (discriminant < 0)
		return (-1.0);
	return (h - sqrtf(discriminant) / a);
}

uint32_t	ray_color(t_ray ray)
{
	t_vector3	unit_dir;
	t_vector3	norm;
	double		t;

	//Testing spheres
	t = hit_sphere((t_vector3){0, 0, -1}, 0.5, ray);
	if (t > 0.0)
	{
		norm = vec3_normal(vec3_subtract(vec3_at_tip(ray, t), (t_vector3){0, 0, -1}));
		// Scale the normal vector components to [0, 1] range
		return (assign_color(255 * (0.5 * (norm.x + 1)),
							 255 * (0.5 * (norm.y + 1)),
							 255 * (0.5 * (norm.z + 1))));
	}

	unit_dir = vec3_normal(ray.dir);
	t = 0.5 * (unit_dir.y + 1.0);
	return (assign_color(128 * (t), 178 * (t), 255 * (t))
		+ assign_color(255 * (1.0-t), 255 * (1.0-t), 255 * (1.0-t)));
}

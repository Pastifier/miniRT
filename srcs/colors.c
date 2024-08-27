/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:00:07 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/27 22:06:16 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "minirt.h"
#include "vectors.h"
#include "ray.h"
#include "log.h"
#include <math.h>

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
	if (r < 0.0f)
		r = 0.0f;
	if (r > 1.0f)
		r = 1.0f;
	if (g < 0.0f)
		g = 0.0f;
	if (g > 1.0f)
		g = 1.0f;
	if (b < 0.0f)
		b = 0.0f;
	if (b > 1.0f)
		b = 1.0f;
	uint8_t red = (uint8_t)(r * 255.0f);
	uint8_t green = (uint8_t)(g * 255.0f);
	uint8_t blue = (uint8_t)(b * 255.0f);
	uint32_t rgb = (red << 16) | (green << 8) | blue;
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
	double		a;
	t_vector3	normal;
	t_vector3	light_normal;
	t_vector3	circle;

	circle = (t_vector3){0, 0, -1};
	a = hit_sphere(circle, 0.5, ray);
	if (a > 0.0)
	{
		normal = vec3_normal(vec3_subtract(vec3_at_tip(ray, a), circle));
		light_normal = vec3_normal((t_vector3){0, 0, 1});
		return (convert_to_color(vec3_dot(normal, light_normal), 0.0, 0.0));
	}
	normal = vec3_normal(ray.dir);
	a = 0.5 * (normal.y + 1.0);
	return (assign_color(0xFF * (1 - a) , 0xFF * (1 - a), 0xFF * (1 - a))
			+ assign_color(0xFF * 0.5 * a, 0xFF * 0.7 * a, 0xFF * a));
}

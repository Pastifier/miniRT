/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:10:50 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 12:53:59 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "ray.h"

double	vec3_dot(t_vector3 u, t_vector3 v)
{
	return ((u.x * v.x) + (u.y * v.y) + (u.z * v.z));
}

t_vector3	vec3_cross(t_vector3 u, t_vector3 v)
{
	return ((t_vector3)
		{
			.x = u.y * v.z - u.z * v.y,
			.y = u.z * v.x - u.x * v.z,
			.z = u.x * v.y - u.y * u.x
		});
}

t_vector3	vec3_normal(t_vector3 v)
{
	return ((t_vector3)
		{
			.x = v.x / vec3_magnitude(v),
			.y = v.y / vec3_magnitude(v),
			.z = v.z / vec3_magnitude(v),
		});
}
t_vector3	vec3_at_tip(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scaleby(ray.dir, t)));
}
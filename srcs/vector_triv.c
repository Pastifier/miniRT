/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_triv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:51:55 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 11:54:40 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "math.h"

// @warning you need to catch floating-point
// exceptions before applying any of these functions!

t_vector3	vec3_subtract(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector3	vec3_add(t_vector3 a, t_vector3 b)
{
	t_vector3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector3	vec3_scaleby(t_vector3 a, double f)
{
	t_vector3	result;

	result.x = a.x * f;
	result.y = a.y * f;
	result.z = a.z * f;
	return (result);
}

double	vec3_magnitude(t_vector3 a)
{
	return (sqrt(vec3_magnitude_sqrd(a)));
}

double	vec3_magnitude_sqrd(t_vector3 a)
{
	return ((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
}

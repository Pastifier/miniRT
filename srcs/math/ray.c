/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:39:13 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 04:26:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"
#include "matrix.h"

t_ray	ray(t_double4 origin, t_double4 direction)
{
	return ((t_ray)
	{
		.origin = origin,
		.direction = direction
	});
}

t_double4	position(t_ray *r, double t)
{
	t_double4	result;

	d4mul(&result, &r->direction, t);
	d4add(&result, &result, &r->origin);
	return (result);
}

t_ray	m4r_transform(t_ray *r, t_mat4x4 *m)
{
	t_ray	result;

	result.origin = mat4x4_cross_vec(m, &r->origin);
	result.direction = mat4x4_cross_vec(m, &r->direction);
	return (result);
}

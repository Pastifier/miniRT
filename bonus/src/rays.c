/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 05:05:39 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/27 05:21:58 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ray_create(t_ray *ray, t_vec4s *origin, t_vec4s *direction)
{
	ray->origin = *origin;
	ray->dir = *direction;
}

void	ray_position(t_vec4s *result, const t_ray *ray, float t)
{
	const t_vec4s	scaled_dir = lag_vec4s_scaleby_ret(ray->dir, t);
	const t_vec4s	sum = lag_vec4s_add_ret(ray->origin, scaled_dir);
	//result->x = ray->origin.x + ray->dir.x * t;
	//result->y = ray->origin.y + ray->dir.y * t;
	//result->z = ray->origin.z + ray->dir.z * t;
	//result->w = 1.0;
	*result = lag_vec4s_ret(sum.x, sum.y, sum.z, 1.f);
}

void	ray_transform(t_ray *ray, const t_mat4s *matrix)
{
	const t_vec4s	origin = ray->origin;
	const t_vec4s	dir = ray->dir;

	//origin = ray->origin;
	//dir = ray->dir;
	ray->origin = lag_mat4s_cross_vec4s(*matrix, origin); //mat4x4_cross_vec(matrix, &origin);
	ray->dir = lag_mat4s_cross_vec4s(*matrix, dir); //mat4x4_cross_vec(matrix, &dir);
}
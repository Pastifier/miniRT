/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:34:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 10:47:04 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

t_vector3	multiply_mtrx3_vec3(t_matrix3 m, t_vector3 v)
{
	return ((t_vector3)
		{
			.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z,
			.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z,
			.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z
		});
}

t_matrix3	multiply_mtrx3_mtrx3(t_matrix3 a, t_matrix3 b)
{
	t_matrix3	result;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			result.m[i][j] = 0;
			k = -1;
			while (++k < 3)
				result.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (result);
}

t_matrix3	transpose_mtrx3(t_matrix3 m)
{
	t_matrix3	result;
	int			i;
	int			j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			result.m[i][j] = m.m[j][i];
	}
	return (result);
}

t_matrix3	identity_mtrx3(void)
{
	return ((t_matrix3)
		{
			.m = {
				{1, 0, 0},
				{0, 1, 0},
				{0, 0, 1}
			}
		});
}

t_matrix3	rotation_mtrx3(t_vector3 axis, double angle)
{
	t_matrix3	result;
	double		c;
	double		s;

	c = cos(angle);
	s = sin(angle);
	result.m[0][0] = c + axis.x * axis.x * (1 - c);
	result.m[0][1] = axis.x * axis.y * (1 - c) - axis.z * s;
	result.m[0][2] = axis.x * axis.z * (1 - c) + axis.y * s;
	result.m[1][0] = axis.y * axis.x * (1 - c) + axis.z * s;
	result.m[1][1] = c + axis.y * axis.y * (1 - c);
	result.m[1][2] = axis.y * axis.z * (1 - c) - axis.x * s;
	result.m[2][0] = axis.z * axis.x * (1 - c) - axis.y * s;
	result.m[2][1] = axis.z * axis.y * (1 - c) + axis.x * s;
	result.m[2][2] = c + axis.z * axis.z * (1 - c);
	return (result);
}

t_matrix3	scale_mtrx3(t_vector3 scale)
{
	return ((t_matrix3)
		{
			.m = {
				{scale.x, 0, 0},
				{0, scale.y, 0},
				{0, 0, scale.z}
			}
		});
}

t_matrix3	translation_mtrx3(t_vector3 translation)
{
	return ((t_matrix3)
		{
			.m = {
				{1, 0, translation.x},
				{0, 1, translation.y},
				{0, 0, translation.z}
			}
		});
}

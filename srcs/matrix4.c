/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:39:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 10:46:34 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>

t_vector3	multiply_mtrx4_vec3(t_matrix4 m, t_vector3 v)
{
	return ((t_vector3)
		{
			.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2]
			* v.z + m.m[0][3],
			.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2]
			* v.z + m.m[1][3],
			.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2]
			* v.z + m.m[2][3]
		});
}

t_matrix4	multiply_mtrx4_mtrx4(t_matrix4 a, t_matrix4 b)
{
	t_matrix4	result;
	int			i;
	int			j;
	int			k;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			result.m[i][j] = 0;
			k = -1;
			while (++k < 4)
				result.m[i][j] += a.m[i][k] * b.m[k][j];
		}
	}
	return (result);
}

t_matrix4	transpose_mtrx4(t_matrix4 m)
{
	t_matrix4	result;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			result.m[i][j] = m.m[j][i];
	}
	return (result);
}

t_matrix4	identity_mtrx4(void)
{
	t_matrix4	result;
	int			i;
	int			j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			result.m[i][j] = (i == j);
	}
	return (result);
}

t_matrix4	rotation_mtrx4(t_vector3 axis, double angle)
{
	t_matrix4	result;
	double		c;
	double		s;

	c = cos(angle);
	s = sin(angle);
	result = identity_mtrx4();
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

t_matrix4	scale_mtrx4(t_vector3 scale)
{
	t_matrix4	result;

	result = identity_mtrx4();
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	return (result);
}

t_matrix4	translation_mtrx4(t_vector3 translation)
{
	t_matrix4	result;

	result = identity_mtrx4();
	result.m[0][3] = translation.x;
	result.m[1][3] = translation.y;
	result.m[2][3] = translation.z;
	return (result);
}

t_matrix4	look_at_mtrx4(t_vector3 from, t_vector3 to, t_vector3 up)
{
	t_matrix4	result;
	t_vector3	f;
	t_vector3	r;
	t_vector3	u;

	f = vec3_normal(vec3_subtract(to, from));
	r = vec3_normal(vec3_cross(f, up));
	u = vec3_cross(r, f);
	result = identity_mtrx4();
	result.m[0][0] = r.x;
	result.m[0][1] = r.y;
	result.m[0][2] = r.z;
	result.m[1][0] = u.x;
	result.m[1][1] = u.y;
	result.m[1][2] = u.z;
	result.m[2][0] = -f.x;
	result.m[2][1] = -f.y;
	result.m[2][2] = -f.z;
	result.m[0][3] = -vec3_dot(r, from);
	result.m[1][3] = -vec3_dot(u, from);
	result.m[2][3] = vec3_dot(f, from);
	return (result);
}

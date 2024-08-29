/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 04:54:04 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 09:35:47by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"
#include <stdbool.h>

bool	mat4x4_eq(t_mat4x4 *m1, t_mat4x4 *m2)
{
	int	r;

	r = -1;
	while (++r < 4)
		if (!d4eq((t_double4 *)&m1->m[r][0], (t_double4 *)&m2->m[r][0]))
			return (false);
	return (true);
}

t_mat4x4	mat4x4_cross(t_mat4x4 *m1, t_mat4x4 *m2)
{
	t_mat4x4	result;
	int			r;
	int			c;

	r = -1;
	while (++r < 4)
	{
		c = -1;
		while (++c < 4)
		{
			result.m[r][c] = m1->m[r][0] * m2->m[0][c]
				+ m1->m[r][1] * m2->m[1][c]
				+ m1->m[r][2] * m2->m[2][c]
				+ m1->m[r][3] * m2->m[3][c];
		}
	}
	return (result);
}

t_double4	mat4x4_cross_vec(t_mat4x4 *m, t_double4 *v)
{
	t_double4	result;

	result.x = vdot(&m->r1, v);
	result.y = vdot(&m->r2, v);
	result.z = vdot(&m->r3, v);
	result.w = vdot(&m->r4, v);
	return (result);
}

t_mat4x4	mat4x4_transpose(t_mat4x4 *m)
{
	t_mat4x4	result;

	result.r1 = row4(m->m[0][0], m->m[1][0], m->m[2][0], m->m[3][0]);
	result.r2 = row4(m->m[0][1], m->m[1][1], m->m[2][1], m->m[3][1]);
	result.r3 = row4(m->m[0][2], m->m[1][2], m->m[2][2], m->m[3][2]);
	result.r4 = row4(m->m[0][3], m->m[1][3], m->m[2][3], m->m[3][3]);
	return (result);
}

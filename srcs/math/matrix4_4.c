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
	t_double4	column;
	t_double4	*rows;
	int			r;

	rows = &m1->r1;
	r = -1;
	while (++r < 4)
	{
		column = extract_column4(m2, 0);
		result.m[r][0] = vdot(&rows[r], &column);
		column = extract_column4(m2, 1);
		result.m[r][1] = vdot(&rows[r], &column);
		column = extract_column4(m2, 2);
		result.m[r][2] = vdot(&rows[r], &column);
		column = extract_column4(m2, 3);
		result.m[r][3] = vdot(&rows[r], &column);
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

	result.r1 = extract_column4(m, 0);
	result.r2 = extract_column4(m, 1);
	result.r3 = extract_column4(m, 2);
	result.r4 = extract_column4(m, 3);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_4_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:27:52 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/03 12:11:42 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"
#include <stdbool.h>

double	cofactor4x4(t_mat4x4 *m, int row, int col)
{
	t_mat3x3	sub;
	t_mat4x4	intermediate;

	intermediate = submatrix(m, row, col);
	sub.r1 = row3(intermediate.m[0][0], intermediate.m[0][1], 
		intermediate.m[0][2]);
	sub.r2 = row3(intermediate.m[1][0], intermediate.m[1][1], 
		intermediate.m[1][2]);
	sub.r3 = row3(intermediate.m[2][0], intermediate.m[2][1], 
		intermediate.m[2][2]);
	if ((row + col) % 2)
		return (-mat3x3_det(&sub));
	return (mat3x3_det(&sub));
}

double	mat4x4_det(t_mat4x4 *m)
{
	double		result;
	int			c;

	result = 0;
	c = -1;
	while (++c < 4)
		result += m->m[0][c] * cofactor4x4(m, 0, c);
	return (result);
}

t_mat4x4	mat4x4_adjugate(t_mat4x4 *m)
{
	t_mat4x4	adj;
	int			r;
	int			c;

	r = -1;
	while (++r < 4)
	{
		c = -1;
		while (++c < 4)
			adj.m[c][r] = cofactor4x4(m, r, c);
	}
	return (adj);
}

t_mat4x4	mat4x4_inverse(t_mat4x4 *m)
{
	t_mat4x4	adj;
	t_mat4x4	inv;
	double		det;

	det = mat4x4_det(m);
	if (det == 0)
		return (*m);
	adj = mat4x4_adjugate(m);
	inv = adj;
	if (det != 0)
	{
		d4div(&inv.r1, &adj.r1, det);
		d4div(&inv.r2, &adj.r2, det);
		d4div(&inv.r3, &adj.r3, det);
		d4div(&inv.r4, &adj.r4, det);
	}
	return (inv);
}

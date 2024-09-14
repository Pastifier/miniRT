/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4_4_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:27:52 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/14 22:15:25 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"
#include <stdbool.h>

inline double	cofactor4x4(t_mat4x4 *m, int row, int col)
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

	result = 0;
	result += m->m[0][0] * cofactor4x4(m, 0, 0);
	result += m->m[0][1] * cofactor4x4(m, 0, 1);
	result += m->m[0][2] * cofactor4x4(m, 0, 2);
	result += m->m[0][3] * cofactor4x4(m, 0, 3);
	return (result);
}

t_mat4x4	mat4x4_adjugate(t_mat4x4 *m)
{
	t_mat4x4	adj;

	adj.m[0][0] = cofactor4x4(m, 0, 0);
	adj.m[1][0] = cofactor4x4(m, 0, 1);
	adj.m[2][0] = cofactor4x4(m, 0, 2);
	adj.m[3][0] = cofactor4x4(m, 0, 3);
	adj.m[0][1] = cofactor4x4(m, 1, 0);
	adj.m[1][1] = cofactor4x4(m, 1, 1);
	adj.m[2][1] = cofactor4x4(m, 1, 2);
	adj.m[3][1] = cofactor4x4(m, 1, 3);
	adj.m[0][2] = cofactor4x4(m, 2, 0);
	adj.m[1][2] = cofactor4x4(m, 2, 1);
	adj.m[2][2] = cofactor4x4(m, 2, 2);
	adj.m[3][2] = cofactor4x4(m, 2, 3);
	adj.m[0][3] = cofactor4x4(m, 3, 0);
	adj.m[1][3] = cofactor4x4(m, 3, 1);
	adj.m[2][3] = cofactor4x4(m, 3, 2);
	adj.m[3][3] = cofactor4x4(m, 3, 3);
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
	d4div(&inv.r1, &adj.r1, det);
	d4div(&inv.r2, &adj.r2, det);
	d4div(&inv.r3, &adj.r3, det);
	d4div(&inv.r4, &adj.r4, det);
	return (inv);
}

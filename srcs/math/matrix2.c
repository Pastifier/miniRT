/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:05:52 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 10:09:04 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"

double	cofactor(t_mat4x4 *m, int row, int col)
{
	double		minor;

	minor = mat_minor(m, row, col);
	if ((row + col) % 2)
		minor = -minor;
	return (minor);
}

t_double4	extract_column4(t_mat4x4 *m, int col)
{
	t_double4	v;

	v.x = m->m[0][col];
	v.y = m->m[1][col];
	v.z = m->m[2][col];
	v.w = m->m[3][col];
	return (v);
}

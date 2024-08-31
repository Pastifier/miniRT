/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:13:29 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/30 21:30:23 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"

t_mat4x4	shearing(double xy, double xz, double yx,
	double yz, double zx, double zy)
{
	return ((t_mat4x4)
	{
		.r1 = row4(1, xy, xz, 0),
		.r2 = row4(yx, 1, yz, 0),
		.r3 = row4(zx, zy, 1, 0),
		.r4 = row4(0, 0, 0, 1)
	});
}

void	m4d_shear(t_double4 *p, double xy, double xz, double yx,
	double yz, double zx, double zy)
{
	t_mat4x4	m;

	m = shearing(xy, xz, yx, yz, zx, zy);
	*p = mat4x4_cross_vec(&m, p);
}
// 
t_double4	m4d_rot_scale_trans(t_double4 *p, t_mat4x4 *rot, t_mat4x4 *scale,
	t_mat4x4 *trans)
{
	t_double4	tmp;

	tmp = mat4x4_cross_vec(rot, p);
	tmp = mat4x4_cross_vec(scale, &tmp);
	tmp = mat4x4_cross_vec(trans, &tmp);
	return (tmp);
}

t_mat4x4	mat4x4_identity(void)
{
	return ((t_mat4x4)
	{
		.r1 = row4(1, 0, 0, 0),
		.r2 = row4(0, 1, 0, 0),
		.r3 = row4(0, 0, 1, 0),
		.r4 = row4(0, 0, 0, 1)
	});
}

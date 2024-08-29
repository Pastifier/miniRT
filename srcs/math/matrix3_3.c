/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:26:43 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 10:27:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"

double	mat3x3_det(t_mat3x3 *m)
{
	double		result;
	t_mat4x4	m4;

	m4.r1 = row4(m->r1.x, m->r1.y, m->r1.z, 0);
	m4.r2 = row4(m->r2.x, m->r2.y, m->r2.z, 0);
	m4.r3 = row4(m->r3.x, m->r3.y, m->r3.z, 0);
	m4.r4 = row4(0, 0, 0, 1);
	result = m->r1.x * cofactor(&m4, 0, 0)
		+ m->r1.y * cofactor(&m4, 0, 1)
		+ m->r1.z * cofactor(&m4, 0, 2);
	return (result);
}

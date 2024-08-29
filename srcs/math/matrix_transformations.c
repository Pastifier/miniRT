/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:45:14 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 18:09:05 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"
#include "libft.h"

t_mat4x4	translation(double x, double y, double z)
{
	t_mat4x4	m;

	m.r1 = row4(1, 0, 0, x);
	m.r2 = row4(0, 1, 0, y);
	m.r3 = row4(0, 0, 1, z);
	m.r4 = row4(0, 0, 0, 1);
	return (m);
}

t_mat4x4	scaling(double x, double y, double z)
{
	t_mat4x4	m;

	m.r1 = row4(x, 0, 0, 0);
	m.r2 = row4(0, y, 0, 0);
	m.r3 = row4(0, 0, z, 0);
	m.r4 = row4(0, 0, 0, 1);
	return (m);
}

t_mat4x4	rotation_x(double rad)
{
	t_mat4x4	m;

	m.r1 = row4(1, 0, 0, 0);
	m.r2 = row4(0, cos(rad), -sin(rad), 0);
	m.r3 = row4(0, sin(rad), cos(rad), 0);
	m.r4 = row4(0, 0, 0, 1);
	return (m);
}

t_mat4x4	rotation_y(double rad)
{
	return ((t_mat4x4)
	{
		.r1 = row4(cos(rad), 0, sin(rad), 0),
		.r2 = row4(0, 1, 0, 0),
		.r3 = row4(-sin(rad), 0, cos(rad), 0),
		.r4 = row4(0, 0, 0, 1)
	});
}

t_mat4x4	rotation_z(double rad)
{
	return ((t_mat4x4)
	{
		.r1 = row4(cos(rad), -sin(rad), 0, 0),
		.r2 = row4(sin(rad), cos(rad), 0, 0),
		.r3 = row4(0, 0, 1, 0),
		.r4 = row4(0, 0, 0, 1)
	});
}

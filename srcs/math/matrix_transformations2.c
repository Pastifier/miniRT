/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:29:54 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 17:23:04 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "linear_algebra.h"

void	m4d_translate(t_double4 *p, double x, double y, double z)
{
	t_mat4x4	m;

	m = translation(x, y, z);
	*p = mat4x4_cross_vec(&m, p);
}

void	m4d_scale(t_double4 *p, double x, double y, double z)
{
	t_mat4x4	m;

	m = scaling(x, y, z);
	*p = mat4x4_cross_vec(&m, p);
}

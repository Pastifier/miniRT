/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 01:58:38 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 02:16:49y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"

t_mat4x4	mat4x4(t_double4 r1, t_double4 r2, t_double4 r3, t_double4 r4)
{
	t_mat4x4	m;

	m.r1 = r1;
	m.r2 = r2;
	m.r3 = r3;
	m.r4 = r4;
	return (m);
}

t_mat3x3	mat3x3(t_double3 r1, t_double3 r2, t_double3 r3)
{
	t_mat3x3	m;

	ft_bzero(&m, sizeof(t_mat3x3));
	m.r1 = r1;
	m.r2 = r2;
	m.r3 = r3;
	return (m);
}

t_mat2x2	mat2x2(t_double2 r1, t_double2 r2)
{
	t_mat2x2	m;

	ft_bzero(&m, sizeof(t_mat2x2));
	m.r1 = r1;
	m.r2 = r2;
	return (m);
}

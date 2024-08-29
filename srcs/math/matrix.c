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

t_mat4x4	submatrix(t_mat4x4 *m, int row, int col)
{
	t_mat4x4	sub;
	int		r;
	int		c;
	int		r2;
	int		c2;

	ft_bzero(&sub, sizeof(t_mat4x4));
	r2 = 0;
	r = -1;
	while (++r < 4)
	{
		if (r == row)
			continue ;
		c2 = 0;
		c = -1;
		while (++c < 4)
		{
			if (c == col)
				continue ;
			sub.m[r2][c2] = m->m[r][c];
			c2++;
		}
		r2++;
	}
	return (sub);
}

double	mat_minor(t_mat4x4 *m, int row, int col)
{
	t_mat4x4	sub;
	double		det;
	t_mat2x2	m2;

	sub = submatrix(m, row, col);
	m2.r1 = row2(sub.m[0][0], sub.m[0][1]);
	m2.r2 = row2(sub.m[1][0], sub.m[1][1]);
	det = mat2x2_det(&m2);
	return (det);
}

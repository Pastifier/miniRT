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


t_mat4x4 mat4x4_cross(t_mat4x4 *m1, t_mat4x4 *m2)
{
	t_mat4x4	result;
	__m256d		row;
	__m256d		col[4];
	int			r;

	col[0] = avx_extract_column(m2, 0);
	col[1] = avx_extract_column(m2, 1);
	col[2] = avx_extract_column(m2, 2);
	col[3] = avx_extract_column(m2, 3);
	r = -1;
	while (++r < 4)
	{
		row = _mm256_set_pd(m1->m[r][3], m1->m[r][2], m1->m[r][1], m1->m[r][0]);
		result.m[r][0] = avx_dot_product(row, col[0]);
		result.m[r][1] = avx_dot_product(row, col[1]);
		result.m[r][2] = avx_dot_product(row, col[2]);
		result.m[r][3] = avx_dot_product(row, col[3]);
	}
	return (result);
}
//t_mat4x4 mat4x4_cross(t_mat4x4 *m1, t_mat4x4 *m2)
//{
//	int r;
//	t_double4 col;
//	t_mat4x4 result;
//	t_double4 *row;

//	r = -1;
//	row = &(m1->r1);
//	while (++r < 4)
//	{
//		col = extract_column(m2, 0);
//		result.m[r][0] = vdot(&row[r], &col);
//		col = extract_column(m2, 1);
//		result.m[r][1] = vdot(&row[r], &col);
//		col = extract_column(m2, 2);
//		result.m[r][2] = vdot(&row[r], &col);
//		col = extract_column(m2, 3);
//		result.m[r][3] = vdot(&row[r], &col);
//	}
//	return (result);
//}

bool	mat4x4_eq(t_mat4x4 *m1, t_mat4x4 *m2)
{
	int	r;

	r = -1;
	if (!d4eq((t_double4 *)&m1->m[r][0], (t_double4 *)&m2->m[r][0]))
		return (false);
	if (!d4eq((t_double4 *)&m1->m[r][1], (t_double4 *)&m2->m[r][1]))
		return (false);
	if (!d4eq((t_double4 *)&m1->m[r][2], (t_double4 *)&m2->m[r][2]))
		return (false);
	if (!d4eq((t_double4 *)&m1->m[r][3], (t_double4 *)&m2->m[r][3]))
		return (false);
	return (true);
}

t_double4	mat4x4_cross_vec(t_mat4x4 *m, t_double4 *v)
{
	t_double4	result;
	__m256d		simd_v;

	simd_v = simdify_double4(v);
	result.x = avx_dot_product(simdify_double4(&m->r1), simd_v);
	result.y = avx_dot_product(simdify_double4(&m->r2), simd_v);
	result.z = avx_dot_product(simdify_double4(&m->r3), simd_v);
	result.w = avx_dot_product(simdify_double4(&m->r4), simd_v);
	return (result);
}

t_mat4x4	mat4x4_transpose(t_mat4x4 *m)
{
	t_mat4x4	result;

	result.r1 = row4(m->m[0][0], m->m[1][0], m->m[2][0], m->m[3][0]);
	result.r2 = row4(m->m[0][1], m->m[1][1], m->m[2][1], m->m[3][1]);
	result.r3 = row4(m->m[0][2], m->m[1][2], m->m[2][2], m->m[3][2]);
	result.r4 = row4(m->m[0][3], m->m[1][3], m->m[2][3], m->m[3][3]);
	return (result);
}

t_mat4x4	mat4x4_identity(void)
{
	t_mat4x4	result;

	result.r1 = row4(1, 0, 0, 0);
	result.r2 = row4(0, 1, 0, 0);
	result.r3 = row4(0, 0, 1, 0);
	result.r4 = row4(0, 0, 0, 1);
	return (result);
}

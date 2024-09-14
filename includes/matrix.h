/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 01:54:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/14 21:23:30 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "rtmath.h"
# include <stdbool.h>
# include <immintrin.h>
# include <assert.h>

//typedef struct s_mat4x4
//{
//	double	m[4][4];
//}	t_mat4x4;

typedef union u_mat4x4
{
	double	m[4][4];
	struct
	{
		t_double4	r1;
		t_double4	r2;
		t_double4	r3;
		t_double4	r4;
	};
}	t_mat4x4;

typedef union u_mat3x3
{
	double	m[3][3];
	struct
	{
		t_double3	r1;
		t_double3	r2;
		t_double3	r3;
	};
}	t_mat3x3;

typedef union u_mat2x2
{
	double	m[2][2];
	struct
	{
		t_double2	r1;
		t_double2	r2;
	};
}	t_mat2x2;

static inline t_double4	extract_column(t_mat4x4 *m, short c)
{
	return ((t_double4)
		{
		.x = m->m[0][c],
		.y = m->m[1][c],
		.z = m->m[2][c],
		.w = m->m[3][c]
		});
}

static inline __m256d	avx_extract_column(t_mat4x4 *m, short c)
{
	assert(c >= 0 && c < 4);
	return (_mm256_set_pd(m->m[3][c], m->m[2][c], m->m[1][c], m->m[0][c]));
}

static inline double	avx_dot_product(__m256d a, __m256d b)
{
	__m256d			temp;
	double			result[4];
	const __m256d	mul = _mm256_mul_pd(a, b);

	temp = _mm256_hadd_pd(mul, mul);
	_mm256_storeu_pd(result, temp);
	return (result[0] + result[2]);
}

static inline __m256d	simdify_double4(t_double4 *v)
{
	return (_mm256_set_pd(v->v[3], v->v[2], v->v[1], v->v[0]));
}

t_double4	row4(double x, double y, double z, double w);
t_double4	extract_column4(t_mat4x4 *m, int col);
t_double3	row3(double x, double y, double z);
t_double2	row2(double x, double y);
t_mat4x4	mat4x4(t_double4 r1, t_double4 r2, t_double4 r3, t_double4 r4);
t_mat3x3	mat3x3(t_double3 r1, t_double3 r2, t_double3 r3);
t_mat2x2	mat2x2(t_double2 r1, t_double2 r2);
bool		mat4x4_eq(t_mat4x4 *m1, t_mat4x4 *m2);
t_mat4x4	mat4x4_cross(t_mat4x4 *m1, t_mat4x4 *m2);
t_double4	mat4x4_cross_vec(t_mat4x4 *m, t_double4 *v);
t_mat4x4	mat4x4_transpose(t_mat4x4 *m);
t_mat4x4	submatrix(t_mat4x4 *m, int row, int col);
double		mat2x2_det(t_mat2x2 *m);
double		mat_minor(t_mat4x4 *m, int row, int col);
double		cofactor(t_mat4x4 *m, int row, int col);
double		cofactor4x4(t_mat4x4 *m, int row, int col);
double		mat3x3_det(t_mat3x3 *m);
double		mat4x4_det(t_mat4x4 *m);
t_mat4x4	mat4x4_adjugate(t_mat4x4 *m);
t_mat4x4	mat4x4_inverse(t_mat4x4 *m);
t_mat4x4	mat4x4_identity(void);
t_mat4x4	translation(double x, double y, double z);
t_mat4x4	scaling(double x, double y, double z);
t_mat4x4	rotation_x(double rad);
t_mat4x4	rotation_y(double rad);
t_mat4x4	rotation_z(double rad);
t_mat4x4	shearing(double xy, double xz, double yx,
	double yz, double zx, double zy);
void		m4d_translate(t_double4 *p, double x, double y, double z);
void		m4d_scale(t_double4 *p, double x, double y, double z);
void		m4d_rotate_x(t_double4 *p, double rad);
void		m4d_rotate_y(t_double4 *p, double rad);
void		m4d_rotate_z(t_double4 *p, double rad);
void		m4d_shear(t_double4 *p, double xy, double xz, double yx,
	double yz, double zx, double zy);
t_double4	m4d_rot_scale_trans(t_double4 *p, t_mat4x4 *rot, t_mat4x4 *scale,
	t_mat4x4 *trans);

#endif // !MATRIX_H
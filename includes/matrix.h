/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 01:54:47 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 17:23:32 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "rtmath.h"
# include <stdbool.h>

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
t_mat4x4	translation(double x, double y, double z);
t_mat4x4	scaling(double x, double y, double z);
void		m4d_translate(t_double4 *p, double x, double y, double z);
void		m4d_scale(t_double4 *p, double x, double y, double z);

#endif // !MATRIX_H
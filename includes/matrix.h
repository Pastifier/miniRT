/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:24:47 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 11:40:53 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vectors.h"

typedef struct s_matrix3
{
	double	m[3][3];
}	t_matrix3;

typedef struct matrix4
{
	double	m[4][4];
}	t_matrix4;

//	Matrix 3x3	//

t_vector3	multiply_mtrx3_vec3(t_matrix3 m, t_vector3 v);
t_matrix3	multiply_mtrx3_mtrx3(t_matrix3 a, t_matrix3 b);
t_matrix3	transpose_mtrx3(t_matrix3 m);
t_matrix3	identity_mtrx3(void);
t_matrix3	rotation_mtrx3(t_vector3 axis, double angle);
t_matrix3	scale_mtrx3(t_vector3 scale);
t_matrix3	translation_mtrx3(t_vector3 translation);

//	Matrix 4x4	//

t_vector3	multiply_mtrx4_vec3(t_matrix4 m, t_vector3 v);
t_matrix4	multiply_mtrx4_mtrx4(t_matrix4 a, t_matrix4 b);
t_matrix4	transpose_mtrx4(t_matrix4 m);
t_matrix4	identity_mtrx4(void);
t_matrix4	rotation_mtrx4(t_vector3 axis, double angle);
t_matrix4	scale_mtrx4(t_vector3 scale);
t_matrix4	translation_mtrx4(t_vector3 translation);
t_matrix4	look_at_mtrx4(t_vector3 from, t_vector3 to, t_vector3 up);

#endif // !__MATRIX_H

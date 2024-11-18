/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lag.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 06:33:18 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 10:52:31 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAG_H
# define LAG_H

# include "ltypes.h" // for SSE/AVX(2) instrinsics and Lag types
# include <math.h>

/*--- INIT_PS ---*/

/// @brief Returns a `t_vec4s` with components (x, y, z, w)
t_vec4s	lag_vec4s_ret(float x, float y, float z, float w);

/// @brief Initialises a `t_vec4s` in homogenous coordinates with a w of `1`
void	lag_vec4sp_init(t_vec4s *target, float x, float y,
			float z);

/// @brief Returns a `t_vec4s` in homogenous coordinates with a w of `1`
t_vec4s	lag_vec4sp_ret(float x, float y, float z);

/// @brief Initialises a `t_vec4s` in homogenous coordinates with a w of `0`
void	lag_vec4sv_init(t_vec4s *target, float x, float y,
			float z);

/// @brief Returns a `t_vec4s` in homogenous coordinates with a w of `0`
t_vec4s	lag_vec4sv_ret(float x, float y, float z);

/*--- LINEAR_ALGEBRA ---*/

/// @brief Performs component-wise (vector) addition and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
void	lag_vec4s_add(t_vec4s *out, const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Performs component-wise (vector) addition.
t_vec4s	lag_vec4s_add_ret(const t_vec4s in1, const t_vec4s in2);

/// @brief Performs component-wise (vector) subtraction and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
void	lag_vec4s_sub(t_vec4s *out, const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Performs component-wise (vector) subtraction.
t_vec4s	lag_vec4s_sub_ret(const t_vec4s in1, const t_vec4s in2);

/// @brief Scales a vector by a scalar and stores the result in the vector
///        pointed-to by `out`.
/// @param in Vector to be scaled
/// @param scalar Scalar to scale the vector by
void	lag_vec4s_scaleby(t_vec4s *out, const t_vec4s in,
			float scalar);

/// @brief Scales a vector by a scalar.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
t_vec4s	lag_vec4s_scaleby_ret(const t_vec4s in, float scalar);

/// @brief Negates a vector and stores the result
///        in the vector pointed-to by `out`.
/// @param in Vector to be negated
/// @param out Pointer to the vector that stores the result.
void	lag_vec4s_negate_new(t_vec4s *out, const t_vec4s in);

/// @brief Negates a vector in place.
/// @param target Pointer to vector to be negated
void	lag_vec4s_negate(t_vec4s *target);

/// @brief Negates a vector.
///        This is to be used when performance is not a concern
///        (i.e. modern compilers, single-usage, etc...),
///        or when function-chaining is desired.
t_vec4s	lag_vec4s_negate_ret(const t_vec4s in);

/// @brief Calculates the dot product of two `t_vec4s`, and stores the result
///        in the variable pointed-to by `out`.
/// @param out Pointer to the variable that stores the result.
/// @param in1 Vector to calculate the dot product of
/// @param in2 Vector to calculate the dot product of
void	lag_vec4s_dot(float *out, const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Calculates the dot product of two `t_vec4s`.
float	lag_vec4s_dot_ret(const t_vec4s *in1,
			const t_vec4s *in2);

/// @brief Calculates the magnitude of a `t_vec4s` and stores the result
///        in the variable pointed-to by `out`.
/// @param in Vector to calculate the magnitude of
/// @param out Pointer to the variable that stores the result.
void	lag_vec4s_magnitude(float *out, const t_vec4s in);

/// @brief Calculates the magnitude of a `t_vec4s`.
float	lag_vec4s_magnitude_ret(const t_vec4s in);

/// @brief Calculates the cross product of two `t_vec4s`
///        (ignoring the `w` component) and stores the result
///        in the vector pointed-to by `out`.
/// @param in1, in2 operand
/// @param out Pointer to the vector that stores the result.
void	lag_vec4s_cross(t_vec4s *out, const t_vec4s in1,
			const t_vec4s in2);

/// @brief Calculates the cross product of two `t_vec4s`
///        (ignoring the w component).
t_vec4s	lag_vec4s_cross_ret(const t_vec4s in1,
			const t_vec4s in2);

/// @brief Checks equality of `a` and `b` within a set `tolerance`.
///        `__FLT_EPSILON__` or a value slightly higher works.
/// @param a, b `t_vec4s` vector
/// @param tolerance Desired tolerance.
/// @return `true (1)` or `false (0)`, depending on the comparison result.
/// @warning If either of the values entered contain `NaN`, the result
///          will be `false (0)`.
bool	lag_vec4s_eq(const t_vec4s a, const t_vec4s b,
			float tolerance);

/// @brief Checks EXACT equality of `a` and `b`. Use wisely.
/// @param a, b `t_vec4s` vector
/// @return `true (1)` or `false (0)`, depending on the comparison result.
/// @warning If either of the values entered contain `NaN`, the result
///          will be `false (0)`.
bool	lag_vec4s_exacteq(const t_vec4s a, const t_vec4s b);

/// @brief Normalizes a `t_vec4s` in place.
/// @param target Pointer to `t_vec4s` to be normalized
/// @warning Recommend using an EPSILON of around `0.0001`.
///          For better precision, use `lag_vec4s_normalize_mediump`.
///          For highest precision, use `lag_vec4s_normalize_highp`.
void	lag_vec4s_normalize(t_vec4s *target);

/// @brief Returns a normalized version of the `t_vec4s`: `in`.
/// @param in `t_vec4s` to be normalized.
/// @warning Recommend using an EPSILON of around `0.0001`.
///          For better precision, use `lag_vec4s_normalize_mediump`.
///          For highest precision, use `lag_vec4s_normalize_highp`.
t_vec4s	lag_vec4s_normalize_ret(const t_vec4s in);

/// @brief Normalizes a `t_vec4s` and stores the result
///        in the `t_vec4s` pointed-to by `out`.
/// @param out Pointer to the `t_vec4s` that stores the result.
/// @param in `t_vec4s` to be normalized.
/// @warning Recommend using an EPSILON of around `0.0001`.
///          For better precision, use `lag_vec4s_normalize_mediump`.
///          For highest precision, use `lag_vec4s_normalize_highp`.
void	lag_vec4s_normalize_new(t_vec4s *out, const t_vec4s in);

/// @brief Returns a `t_mat4s` using the parameters as its rows.
t_mat4s	lag_mat4s_rows_ret(const t_vec4s r1, const t_vec4s r2,
			const t_vec4s r3, const t_vec4s r4);

/// @brief Returns a `t_mat4s` identity matrix.
t_mat4s	lag_mat4s_identity(void);

/// @brief Returns a `t_mat4s` affine translation-matrix
///        (`r4 = {0, 0, 0, 1}`).
t_mat4s	lag_mat4s_translation(float tx, float ty, float tz);

/// @brief Returns a `t_mat4s` affine scaling-matrix.
///        (`r4 = {0, 0, 0, 1}`).
t_mat4s	lag_mat4s_scaling(float sx, float sy, float sz);

/// @brief Returns a rotation matrix around the x-axis.
/// @param rad Rotation in radians
t_mat4s	lag_mat4s_rotation_x(float rad);

/// @brief Returns a rotation matrix around the y-axis.
/// @param rad Rotation in radians
t_mat4s	lag_mat4s_rotation_y(float rad);

/// @brief Returns a rotation matrix around the z-axis.
/// @param rad Rotation in radians
t_mat4s	lag_mat4s_rotation_z(float rad);

/// @brief Returns the cross product of a `t_mat4s` with a `t_vec4s`
///        (in that order).
void	lag_mat4s_cross_vec4s(const t_mat4s *m,
			const t_vec4s *v, t_vec4s *out);

/// @brief computes the cross product of `in1` with `in2`
///        (in that order), and stores the result in the `t_mat4s`
///        pointed-to by `out`.
void	lag_mat4s_cross_mat4s(const t_mat4s in1,
			const t_mat4s in2, t_mat4s *out);

/// @brief Calculates the inverse of a decomposed matrix
/// (rotation, scale, translation)
/// @param rot The rotational component of the matrix
/// @param s The scale factor of the matrix
/// @param t The translation component of the matrix
/// @return The inverse of the decomposed matrix
/// @warning The scale should NOT contain any zero components as that will
/// cause a floating-point exception.
t_mat4s	lag_mat4s_get_transform_inverse(const t_mat4s rot, const __m128 s,
			const __m128 t);

/*--- PS_EXTRA ---*/

/// @brief Returns a normalized version of the `t_vec4s`: `in`.
/// @param in `t_vec4s` to be normalized.
t_vec4s	lag_vec4s_normalize_mediump(const t_vec4s in);

/// @brief Returns a normalized version of the `t_vec4s`: `in`.
/// @param in `t_vec4s` to be normalized.
t_vec4s	lag_vec4s_normalize_highp(const t_vec4s in);

#endif // !LAG_H
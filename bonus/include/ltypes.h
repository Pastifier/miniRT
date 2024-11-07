/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltypes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 20:13:25 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/07 16:07:59 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LTYPES_H
# define LTYPES_H

# include <immintrin.h> // For AVX/SSE intrinsics (__m256d, __m128)
# include <stdint.h> // For bit-wise magic (having the option is nice)
# include <stdbool.h> // for `true`, `false`

# ifndef EPSILON
#  define EPSILON 0.0001
# endif // !EPSILON
/*--- VECTOR ---*/

typedef union u_vec4d
{
	float		a[4];
	__m256d		simd;
	uint64_t	raw[4];
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
}__attribute((aligned(32)))	t_vec4d;

typedef union u_vec4s
{
	float		a[4];
	__m128		simd;
	uint32_t	raw[4];
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
}__attribute((aligned(16)))	t_vec4s;

typedef union u_vec3d
{
	float	a[4];
	__m256d	simd;
	struct
	{
		float	x;
		float	y;
		float	z;
		float	ignore;
	};
}__attribute((aligned(32)))	t_vec3d;

typedef union u_vec2d
{
	float	a[2];
	__m128d	simd;
	struct
	{
		float	x;
		float	y;
	};
}__attribute((aligned(16)))	t_vec2d;

/*--- MATRIX ---*/

typedef t_vec4d	t_vec4d; // To silence faulty(?) VS Code warning:

// 2D Matrices can be held inside a single 128-bit vector, fix. (for all)
typedef union u_mat2d
{
	float	a[2][2];
	__m128d	simd[2];
	struct
	{
		t_vec2d	r1;
		t_vec2d	r2;
	};
}__attribute((aligned(16)))	t_mat2d;

typedef union u_mat3d
{
	float	a[4][4];
	__m256	simd[4];
	struct
	{
		t_vec3d	r1;
		t_vec3d	r2;
		t_vec3d	r3;
		t_vec3d	ignore;
	};
}__attribute((aligned(32)))	t_mat3d;

typedef union u_mat4s
{
	float	a[4][4];
	__m128	simd[4];
	__m256	_ymm[2];
	struct
	{
		t_vec4s	r1;
		t_vec4s	r2;
		t_vec4s	r3;
		t_vec4s	r4;
	};
}__attribute((aligned(16)))	t_mat4s;

typedef union u_mat4d
{
	float	a[4][4];
	__m256d	simd[4];
	struct
	{
		t_vec4d	r1;
		t_vec4d	r2;
		t_vec4d	r3;
		t_vec4d	r4;
	};
}__attribute((aligned(32)))	t_mat4d;

typedef t_mat4d	t_mat4d; //"Reference to incomplete type <T> not allowed".

#endif // !LTYPES_H
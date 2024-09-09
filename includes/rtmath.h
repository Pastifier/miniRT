/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:06:09 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/08 23:42:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTMATH_H
# define RTMATH_H

/*
	DESCRIPTION:
	This file contains a bunch of typedefs and utilities regarding
	vectors, points and other stuff.
*/

# include <math.h> // for floating-point utility functions and macros
# include <stdint.h> // for exact-sized types

# ifndef EPSILON
#  define EPSILON 0.00001f
# endif // !EPSILON

# ifndef NULL
#  define NULL (void *)0
# endif // !NULL

typedef union u_double4
{
	double	v[4];
	struct
	{
		double	x;
		double	y;
		double	z;
		double	w;
	};
}	t_double4;

typedef union s_double3
{
	double	v[3];
	struct
	{
		double	x;
		double	y;
		double	z;
	};
}	t_double3;

typedef union s_double2
{
	double	v[2];
	struct
	{
		double	x;
		double	y;
	};
}	t_double2;

typedef struct s_color
{
	double		r;
	double		g;
	double		b;
	t_double4	set;
}	t_color;

typedef struct s_ray
{
	t_double4		origin;
	t_double4		direction;
	t_color			c;
}	t_ray;

#endif // !RTMATH_H
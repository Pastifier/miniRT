/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:06:09 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/02 14:50:55 by melshafi         ###   ########.fr       */
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
# include <stdlib.h>

# ifndef EPSILON
#  define EPSILON 0.00001
# endif // !EPSILON

#define MAX_INTERSECTIONS 4

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

typedef struct s_double3
{
	double	v[3];
	struct
	{
		double	x;
		double	y;
		double	z;
	};
}	t_double3;

typedef struct s_double2
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

typedef struct	s_intersection
{
	double t;
	short object_type;
	void *object;
	t_double4 itx_p;
}	t_intersection;

typedef struct	s_intersections
{
	t_intersection data[MAX_INTERSECTIONS];
	short count;
}	t_intersections;

t_intersection	*get_hit(t_intersections *xs);
void quick_sort_intersections(t_intersection *arr, size_t size);
void sort_intersections(t_intersections *intersects);
void store_intersections(t_intersections *intersects, double t_values[], int object_type, void *object);

#endif // !RTMATH_H

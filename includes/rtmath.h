/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtmath.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:06:09 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/17 13:11:41 by melshafi         ###   ########.fr       */
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
# include <stdbool.h> // for boolean types
# include <stdlib.h>

# ifndef EPSILON
#  define EPSILON 0.00001
# endif // !EPSILON

#define MAX_INTERSECTIONS 400

typedef struct s_object t_object;
typedef struct s_world t_world;
typedef struct s_ray t_ray;

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
	t_object *object;
	t_double4 itx_p;
}	t_intersection;

typedef struct	s_intersections
{
	t_intersection	data[MAX_INTERSECTIONS];
	int				count;
}	t_intersections;

typedef struct	itx_computation
{
	bool		shadowed;
	double		t;
	t_object	*obj;
	t_double4	p;
	t_double4	over_point;
	t_double4	under_point;
	t_double4	eyev;
	t_double4	normalv;
	t_double4	reflectv;
	int			inside;
	double		n1;
	double		n2;
}	t_itx_computation;

typedef t_itx_computation t_comps;

void				prepare_refractions(t_intersection *hit, t_itx_computation *comps, t_intersections *itxs);
t_itx_computation	prepare_computations(t_intersection *itx, t_ray *r, t_intersections	*itxs);
t_intersection		*get_hit(t_intersections *xs);
void				quick_sort_intersections(t_intersection *arr, size_t size);
t_intersections		intersect_world(t_world *w, t_ray *r);
void				store_intersections(t_intersections *intersects, double t_values[], t_object *object);

#endif // !RTMATH_H

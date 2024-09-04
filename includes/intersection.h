/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:30:45 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/04 21:59:58 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION_H
# define INTERSECTION_H

# include "matrix.h"

typedef unsigned long size_t;

enum e_obj_types
{
	SPHERE = 's',
	PLANE = 'p',
	CONE = 'c'
};

typedef struct s_point_light
{
	t_double4	pos;
	t_color		intensity;
}	t_light;

typedef struct s_mat
{
	t_color		c;
	double		amb;
	double		diff;
	double		spec;
	double		shiny;
}	t_mat;

typedef struct s_obj
{
	int				id;
	uint8_t			type;
	t_double4		center;
	double			radius;
	t_mat4x4		transform;
	t_mat			material;
}	t_obj;

typedef struct s_intersection
{
	double		t;
	t_obj		*obj;
	t_double4	p;
	t_double4	over_p;
	t_double4	eye;
	t_double4	s_normal;
	bool		inside;
	bool		got_hit;
}	t_intersection;

typedef struct s_intersections
{
	t_intersection	arr[200];
	int				count;
}	t_intersections;

void			set_transform(t_obj *obj, t_mat4x4 *m);
bool			intersect_sphere(t_ray *r, t_obj *sphere, t_intersections *xs);
void			quick_sort_intersections(t_intersection *arr, size_t size);
t_intersection	*get_hit(t_intersections *xs);
t_double4		normal_at(t_obj *obj, t_double4 *p);
t_double4		reflect(t_double4 *in, t_double4 *s_normal);
t_color			lighting(t_mat *mat, t_light *light, t_intersection *hit,
					bool shadowed);
bool			intersect_plane(t_ray *r, t_obj *plane, t_intersections *xs);

#endif // !INTERSECTION_H
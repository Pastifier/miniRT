/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:30:45 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/31 05:39:11 by ebinjama         ###   ########.fr       */
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

typedef struct s_obj
{
	int				id;
	uint8_t			type;
	t_double4		center;
	double			radius;
	t_mat4x4		transform;
}	t_obj;

typedef struct s_intersection
{
	double	t;
	t_obj	*obj;
	bool	got_hit;
}	t_intersection;

typedef struct s_intersections
{
	t_intersection	arr[200];
	int				count;
}	t_intersections;

void			set_transform(t_obj *obj, t_mat4x4 *m);
bool			hit_sphere(t_ray *r, t_obj *sphere, t_intersections *xs);
t_intersection	*get_hit(t_intersections *xs);
void 			quick_sort(t_intersection *arr, size_t size);
t_double4		normal_at(t_obj *obj, t_double4 *p);

#endif // !INTERSECTION_H
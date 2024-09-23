/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:57:42 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/23 14:51:53 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "libft.h"
#include <stdio.h>

t_itx_computation prepare_computations(t_intersection *itx, t_ray *r, t_intersections *itxs)
{
	t_itx_computation	comps;
	t_double4			margin;

	comps.t = itx->t;
	comps.obj = itx->object;
	ray_position(&comps.p, r, comps.t);
	comps.eyev = r->direction;
	d4negate(&comps.eyev);
	if (itx->object->type == OBJ_SPHERE)
		comps.normalv = sphere_normal_at(itx->object, &comps.p);
	else if (itx->object->type == OBJ_PLANE)
		comps.normalv = plane_normal_at(itx->object);
	else if (itx->object->type == OBJ_CUBE)
		comps.normalv = cube_normal_at(itx->object, &comps.p);
	else if (itx->object->type == OBJ_CYLINDER)
		comps.normalv = cylinder_normal_at(itx->object, &comps.p);
	if (vdot(&comps.normalv, &comps.eyev) < 0)
	{
		comps.inside = true;
		d4negate(&comps.normalv);
	}
	else
		comps.inside = false;
	d4mul(&margin, &comps.normalv, EPSILON);
	d4add(&comps.over_point, &comps.p, &margin);
	d4sub(&comps.under_point, &comps.p, &margin);
	comps.reflectv = reflect(&r->direction, &comps.normalv);
	if (comps.obj->material.refractive_index > 0)
		prepare_refractions(itx, &comps, itxs);
	// (void)itxs;
	return (comps);
}

t_intersections	intersect_world(t_world *w, t_ray *r)
{
	int			i;
	t_intersections	result;

	i = -1;
	result = (t_intersections){0};
	while (++i < w->num_objects)
	{
		if (result.count >= MAX_INTERSECTIONS)
			break ;
		ft_bzero(r->itx.data, sizeof(t_intersection) * MAX_INTERSECTIONS);
		r->itx.count = 0;
		if (w->objects[i].type == OBJ_SPHERE)
			intersect_sphere(r, &w->objects[i], &result);
		else if (w->objects[i].type == OBJ_PLANE)
			intersect_plane(r, &w->objects[i], &result);
		else if (w->objects[i].type == OBJ_CUBE)
			intersect_cube(r, &w->objects[i], &result);
		else if (w->objects[i].type == OBJ_CYLINDER)
			intersect_cylinder(r, &w->objects[i], &result);
	}
	quick_sort_intersections(result.data, result.count);
	return (result);
}

void store_intersections(t_intersections *intersects, double t_values[], t_object *object)
{
	for (int i = 0; i < intersects->count; i++)
	{
		intersects->data[i].t = t_values[i];
		intersects->data[i].object = object;
	}
}

t_intersection	*get_hit(t_intersections *xs)
{
	int		i;

	i = 0;
	while (i < xs->count)
	{
		if (xs->data[i].t >= 0)
			return (&xs->data[i]);
		i++;
	}
	return (NULL);
}

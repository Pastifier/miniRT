/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:29:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/06 12:57:39 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "linear_algebra.h"

bool	intersect_cylinder(t_ray *r, t_obj *cy, t_intersections *xs)
{
	(void)cy;
	double	a, b, c, disc;

	if (xs->count > 199)
		return (false);
	vnormalize(&r->direction);
	a = (r->direction.x * r->direction.x)
		+ (r->direction.z * r->direction.z);
	if (a == 0.0)
		return (false);
	b = (2 * r->origin.x * r->direction.x)
		+ (2 * r->origin.z * r->direction.z);
	c = -1 + (r->origin.x * r->origin.x)
		+ (r->origin.z * r->origin.z);
	disc = (b * b) - (4 * a * c);
	if (disc < 0)
		return (false);
	disc = sqrt(disc);
	xs->arr[xs->count].t = (-b - disc) / (2.0 * a);
	xs->arr[xs->count].got_hit = true;
	xs->arr[xs->count + 1].t = (-b + disc) / (2.0 * a);
	xs->arr[xs->count + 1].got_hit = true;
	xs->count += 2;
	return (true);
}

t_double4	cy_normal_at(t_obj *cy, t_double4 *p)
{
	(void)cy;
	t_double4	norm;

	vector(&norm, p->x, 0, p->z);

	// Checks on whether the point is actualy on the cylinder
	// are unneeded. *p will always be the result of an intersection.
	// Transformations may ensue here

	vnormalize(&norm);
	return (norm);
}

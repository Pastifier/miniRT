/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:43:00 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/03 16:36:01 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "linear_algebra.h"
#include <stdbool.h>
#include "debug.h"

bool	is_shadowed(t_world *w, t_double4 *p)
{
	t_intersections	*xs;
	t_intersection	*hit;
	t_double4		towards_light_from_itx;
	t_ray			r;
	double			distance;

	d4sub(&towards_light_from_itx, &w->plight.pos, p);
	distance = vmag(&towards_light_from_itx);
	vnormalize(&towards_light_from_itx);
	r = ray(*p, towards_light_from_itx);
	xs = intersect_world(w, &r);
	hit = get_hit(xs);
	if ((hit && hit->t >= distance) || !hit)
		return (false);
	return (true);
}

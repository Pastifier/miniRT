/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itx_test_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 07:34:00 by ebinjama          #+#    #+#             */
/*   Updated: 2024/11/18 16:19:37 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_itx_grp	intersect_world(t_world *w, t_ray *r)
{
	t_itx_grp	ret;
	int			i;

	i = -1;
	ret.count = 0;
	while (++i < w->num_shapes)
	{
		if (ret.count >= _RT_MAX_ITX)
			break ;
		if (w->shapes[i].type == SPHERE)
			intersect_sphere(r, &w->shapes[i], &ret);
		else if (w->shapes[i].type == PLANE)
			intersect_plane(r, &w->shapes[i], &ret);
		else if (w->shapes[i].type == CYLINDER)
			intersect_cylinder(r, &w->shapes[i], &ret);
		else if (w->shapes[i].type == CUBE)
			intersect_cube(r, &w->shapes[i], &ret);
		else if (w->shapes[i].type == CONE)
			intersect_cone(r, &w->shapes[i], &ret);
	}
	return (ret);
}

t_itx	*get_hit(t_itx_grp *xs)
{
	int		i;
	float	min;
	t_itx	*addr;

	i = -1;
	min = INFINITY;
	addr = NULL;
	while (++i < xs->count)
	{
		if (xs->arr[i].t < min && xs->arr[i].t >= EPSILON)
		{
			min = xs->arr[i].t;
			addr = &xs->arr[i];
		}
	}
	return (addr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itx_test_world.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 07:34:00 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/31 16:59:38 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"

t_itx_grp	intersect_world(t_world *w, t_ray *r)
{
	t_itx_grp	ret;
	int			i;

	i = -1;
	ret = (t_itx_grp){0};
	while (++i < w->num_shapes)
	{
		if (ret.count >= _RT_MAX_ITX)
			break ;
		if (w->shapes[i].type == SPHERE)
			intersect_sphere(r, &w->shapes[i], &ret);
		if (w->shapes[i].type == PLANE)
			intersect_plane(r, &w->shapes[i], &ret);
	}
	quick_sort_intersections(ret.arr, ret.count); //
	return (ret);
}

t_itx	*get_hit(t_itx_grp *xs) ////
{
	int		i;

	i = -1;
	while (++i < xs->count)
		if (xs->arr[i].t >= 0.f)
			return (&xs->arr[i]);
	return (NULL);
}

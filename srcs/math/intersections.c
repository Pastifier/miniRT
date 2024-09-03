#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "libft.h"
#include <stdio.h>

t_itx_computation prepare_computations(t_intersection itx, t_ray *r)
{
	t_itx_computation	comps;

	comps.t = itx.t;
	comps.obj = itx.object;
	ray_position(&comps.p, r, comps.t);
	comps.eyev = r->direction;
	d4negate(&comps.eyev);
	if (itx.object_type == OBJ_SPHERE)
		comps.normalv = sphere_normal_at(itx.object, &comps.p);
	if (vdot(&comps.normalv, &comps.eyev) < 0)
	{
		comps.inside = true;
		d4negate(&comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_intersections	intersect_world(t_world *w, t_ray *r)
{
	int			i;
	int			j;
	t_intersections	result;

	i = -1;
	result.count = 0;
	while (++i < w->num_objects)
	{
		ft_bzero(r->itx.data, sizeof(t_intersection) * MAX_INTERSECTIONS);
		if (w->objects[i].type == OBJ_SPHERE)
			intersect_sphere(r, &w->objects[i]);
		if (r->itx.count > 0)
		{
			j = -1;
			while (++j < r->itx.count && result.count < MAX_INTERSECTIONS)
			{
				if (r->itx.data[j].t >= 0)
				{
					result.data[result.count] = r->itx.data[j];
					result.count++;
				}
			}
		}
	}
	quick_sort_intersections(result.data, result.count);
	return (result);
}

void store_intersections(t_intersections *intersects, double t_values[], int object_type, void *object)
{
	for (int i = 0; i < intersects->count; i++)
	{
		intersects->data[i].t = t_values[i];
		intersects->data[i].object_type = object_type;
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

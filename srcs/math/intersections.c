#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include <stdio.h>

void store_intersections(t_intersections *intersects, double t_values[], int object_type, void *object)
{
	for (int i = 0; i < intersects->count; i++)
	{
		// intersects->data[intersects->count].t = t_values[i]; // suspicious.
		// intersects->data[intersects->count].object_type = object_type;
		// intersects->data[intersects->count].object = object;

		intersects->data[i].t = t_values[i]; // suspicious.
		intersects->data[i].object_type = object_type;
		intersects->data[i].object = object; // Changed all those to this.
	}
}

t_intersection	*get_hit(t_intersections *xs)
{
	// double	cmp;
	int		i;
	// int		desired;

	i = 0;
	// desired = 0;
	// cmp = INFINITY;
	while (i < xs->count)
	{
		if (xs->data[i].t >= 0 /*&& xs->data[i].t < cmp*/)
		{
			// cmp = xs->data[i].t;
			// desired = i;
			return (&xs->data[i]);
		}
		i++;
	}
	// if (isinf(cmp))
	// 	return (NULL);
	// return (&xs->data[desired]);
	return (NULL);
}

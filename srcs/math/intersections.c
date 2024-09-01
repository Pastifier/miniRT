#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"

void store_intersections(t_intersections *intersects, double t_values[], int object_type, void *object)
{
	for (int i = 0; i < intersects->count && intersects->count < MAX_INTERSECTIONS; i++)
	{
		intersects->data[intersects->count].t = t_values[i];
		intersects->data[intersects->count].object_type = object_type;
		intersects->data[intersects->count].object = object;
		intersects->count++;
	}
}

void sort_intersections(t_intersections *intersects)
{
	for (int i = 0; i < intersects->count - 1; i++)
	{
		for (int j = i + 1; j < intersects->count; j++)
		{
			if (intersects->data[i].t > intersects->data[j].t)
			{
				t_intersection temp = intersects->data[i];
				intersects->data[i] = intersects->data[j];
				intersects->data[j] = temp;
			}
		}
	}
}
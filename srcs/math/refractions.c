/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:57:23 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/17 13:11:53 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "macros.h"
#include "colors.h"
#include <stdio.h>

static void remove_from_container(t_object **container, int *count, int i, t_intersections *itxs)
{
	int j = 0;

	while (j < *count)
	{
		if (container[j] == itxs->data[i].object)
		{
			while (j < *count - 1)
			{
				container[j] = container[j + 1];
				j++;
			}
			(*count)--;
			return;
		}
		j++;
	}
}

static bool within_container(t_object **container, int count, int i, t_intersections *itxs)
{
	for (int j = 0; j < count; j++)
	{
		if (container[j] == itxs->data[i].object)
			return true;
	}
	return false;
}

void prepare_refractions(t_intersection *hit, t_itx_computation *comps, t_intersections *itxs)
{
	int count = 0;
	t_object **container = malloc(sizeof(t_object *) * itxs->count); // Allocate memory for pointers

	comps->n1 = 1.0;
	comps->n2 = 1.0;
	for (int i = 0; i < itxs->count; i++)
	{
		if (&(itxs->data[i]) == hit && count)
			comps->n1 = container[count - 1]->material.refractive_index;
		if (within_container(container, count, i, itxs))
			remove_from_container(container, &count, i, itxs);
		else
			container[count++] = itxs->data[i].object;

		if (&(itxs->data[i]) == hit)
		{
			if (count)
				comps->n2 = container[count - 1]->material.refractive_index;
			break;
		}
	}

	free(container);
}

t_color	refracted_color(t_world *world, t_itx_computation *comps, int depth)
{
	t_color		c;
	t_ray		r;
	t_double4	temp;
	double		n_ratio;
	double		cos_i;
	double		sin2_t;

	color(&c, 0.0, 0.0, 0.0);
	if (depth <= 0 || comps->obj->material.transparency <= 0.0)
		return (c);
	n_ratio = comps->n1 / comps->n2;
	cos_i = vdot(&comps->eyev, &comps->normalv);
	sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
	if (sin2_t > 1.0)
		return (c);
	d4mul(&r.direction, &comps->normalv, n_ratio * cos_i - sqrt(1 - sin2_t));
	d4mul(&temp, &comps->eyev, n_ratio);
	d4sub(&r.direction, &r.direction, &temp);
	r.origin = comps->under_point;
	c = color_at(world, &r, depth - 1);
	cscale(&c, &c, comps->obj->material.transparency);
	return (c);
}

//Replicates the fresnal effect by Augustin-Jean Fresnel with an accurate approximation
//in order to be faster than the original formula, and not incorporate the extras of true Fresnel
//effects like light polarization.
double	schlick(t_itx_computation *comps)
{
	double	cos;
	double	n_ratio;
	double	sin2_t;
	double	cos_t;
	double	r0;

	cos = vdot(&comps->eyev, &comps->normalv);
	if (comps->n1 > comps->n2)
	{
		n_ratio = comps->n1 / comps->n2;
		sin2_t = n_ratio * n_ratio * (1 - cos * cos);
		if (sin2_t > 1.0)
			return (1.0);
		cos_t = sqrt(1.0 - sin2_t);
		cos = cos_t;
	}
	r0 = pow((comps->n1 - comps->n2) / (comps->n1 + comps->n2), 2);
	return (r0 + (1 - r0) * pow(1 - cos, 5));
}
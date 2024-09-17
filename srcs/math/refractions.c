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
#include <stdio.h>

static void remove_from_container(int *container, int *count, int i)
{
	int	j;

	j = -1;
	while (++j < *count)
	{
		if (container[j] == i)
		{
			while (++j < *count)
				container[j - 1] = container[j];
			(*count)--;
			break ;
		}
	}
}

static bool	within_container(int *container, int *count, int i)
{
	int	j;

	j = -1;
	while (++j < *count)
	{
		if (container[j] == i)
			return (true);
	}
	return (false);
}

void	prepare_refractions(t_intersection *hit, t_itx_computation *comps, t_intersections *itxs)
{
	int			i;
	int			count;
	int			*container;

	i = -1;
	container = malloc(sizeof(int) * (itxs->count + 1));
	container[0] = -1;
	count = 0;
	while (++i < itxs->count)
	{
		if (&(itxs->data[i]) == hit)
		{
			if (!count)
				comps->n1 = 1.0;
			else
				comps->n2 = itxs->data[container[count]].object->material.refractive_index;
		}
		printf("i: %d\n", i);
		printf("count: %d\n", count);
		printf("container: %d\n", container[count]);
		printf("itxs->count: %d\n", itxs->count);
		if (within_container(container, &count, i))
			remove_from_container(container, &count, i);
		else
			container[++count] = i;
		if (&(itxs->data[i]) == hit)
		{
			if (!count)
				comps->n2 = 1.0;
			else
				comps->n2 = itxs->data[container[count]].object->material.refractive_index;
			break ;
		}
	}
	free(container);
}

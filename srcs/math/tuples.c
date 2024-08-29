/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:18:54 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 06:11:28 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

void	vector(t_double4 *target, double x, double y, double z)
{
	target->x = x;
	target->y = y;
	target->z = z;
	target->w = 0;
}

void	point(t_double4 *target, double x, double y, double z)
{
	target->x = x;
	target->y = y;
	target->z = z;
	target->w = 1;
}

bool	d4eq(t_double4 *t1, t_double4 *t2)
{
	return (fabs(t1->x - t2->x) < EPSILON
		&& fabs(t1->y - t2->y) < EPSILON
		&& fabs(t1->z - t2->z) < EPSILON
		&& fabs(t1->w - t2->w) < EPSILON);
}

void	d4add(t_double4 *target, t_double4 *t1, t_double4 *t2)
{
	target->x = t1->x + t2->x;
	target->y = t1->y + t2->y;
	target->z = t1->z + t2->z;
	target->w = t1->w + t2->w;
}

void	d4sub(t_double4 *target, t_double4 *t1, t_double4 *t2)
{
	target->x = t1->x - t2->x;
	target->y = t1->y - t2->y;
	target->z = t1->z - t2->z;
	target->w = t1->w - t2->w;
}

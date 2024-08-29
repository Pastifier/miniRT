/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:39:25 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 06:12:26 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

t_double4	row4(double x, double y, double z, double w)
{
	t_double4	t;

	t.x = x;
	t.y = y;
	t.z = z;
	t.w = w;
	return (t);
}

void	d4negate(t_double4 *target)
{
	target->x = -target->x;
	target->y = -target->y;
	target->z = -target->z;
	target->w = -target->w;
}

void	d4mul(t_double4 *target, t_double4 *t1, double scalar)
{
	target->x = t1->x * scalar;
	target->y = t1->y * scalar;
	target->z = t1->z * scalar;
	target->w = t1->w * scalar;
}

void	d4div(t_double4 *target, t_double4 *t1, double scalar)
{
	target->x = t1->x / scalar;
	target->y = t1->y / scalar;
	target->z = t1->z / scalar;
	target->w = t1->w / scalar;
}

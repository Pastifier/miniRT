/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:51:11 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 04:22:29 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

double	vmag(t_double4 *vec)
{
	return (sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

void	vnorm(t_double4 *target, t_double4 *t)
{
	double	mag;

	mag = vmag(t);
	vector(target, t->x / mag, t->y / mag, t->z / mag);
}

void	vnormalize(t_double4 *t)
{
	double	mag;

	mag = vmag(t);
	t->x /= mag;
	t->y /= mag;
	t->z /= mag;
	t->w /= mag;
}

double	vdot(t_double4 *t1, t_double4 *t2)
{
	return (t1->x * t2->x + t1->y * t2->y + t1->z * t2->z
		+ t1->w * t2->w);
}

void	vcross(t_double4 *target, t_double4 *t1, t_double4 *t2)
{
	vector(target,
		t1->y * t2->z - t1->z * t2->y,
		t1->z * t2->x - t1->x * t2->z,
		t1->x * t2->y - t1->y * t2->x);
}

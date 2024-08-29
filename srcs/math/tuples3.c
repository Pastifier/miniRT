/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 04:26:29 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/29 04:27:06 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linear_algebra.h"

t_double3	row3(double x, double y, double z)
{
	t_double3	t;

	t.x = x;
	t.y = y;
	t.z = z;
	return (t);
}

t_double2	row2(double x, double y)
{
	t_double2	t;

	t.x = x;
	t.y = y;
	return (t);
}

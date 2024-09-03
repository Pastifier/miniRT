/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:30 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/03 11:34:41 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"

t_double4	reflect(t_double4 *in, t_double4 *normal)
{
	t_double4 result;
	double dot;

	dot = vdot(in, normal);
	d4mul(&result, normal, 2.0 * dot);
	d4sub(&result, in, &result);
	return (result);
}





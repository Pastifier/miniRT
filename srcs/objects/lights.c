/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:34:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/03 11:34:32 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "colors.h"

t_light	default_point_light(void)
{
	t_light l;

	point(&l.position, -10.0, 10.0, -10.0);
	color(&l.type.point.intensity, 1.0, 1.0, 1.0);
	return (l);
}

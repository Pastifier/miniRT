/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:28:43 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 12:57:13 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "objects.h"

t_object	create_sphere(t_vector3 center, double radius, uint32_t color)
{
	t_object	obj;

	obj.type = SPHERE;
	obj.origin = center;
	obj.u.sphere.radius = radius;
	obj.color = color;
	obj.hit = hit_sphere;
	return (obj);
}

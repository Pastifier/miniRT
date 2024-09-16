/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:33:49 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/03 11:35:53 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "colors.h"

t_material	material(t_color *color, double ambient, double diffuse, double specular, double shininess)
{
	t_material m;

	m.color = *color;
	m.ambient = ambient;
	m.diffuse = diffuse;
	m.specular = specular;
	m.shininess = shininess;
	m.reflective = 0.0;
	m.transparency = 0.0;
	m.refractive_index = 1.0;
	return (m);
}

t_material	default_material(void)
{
	t_material m;

	color(&m.color, 1.0, 1.0, 1.0);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	m.reflective = 0.0;
	m.transparency = 0.0;
	m.refractive_index = 1.0;
	return (m);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:20 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/04 12:42:39 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "rtmath.h"
#include "objects.h"

void	empty_world(t_world *world)
{
	world->num_objects = 0;
	world->num_lights = 0;
}

void	world_add_object(t_world *world, t_object *object)
{
	world->objects[world->num_objects] = *object;
	world->num_objects++;
}

void	world_add_light(t_world *world, t_light *light)
{
	world->lights[world->num_lights] = *light;
	world->num_lights++;
}

void	default_world(t_world *world)
{
	t_object s1;
	t_object s2;
	t_color c;
	t_material m;
	t_material m2;
	t_mat4x4 transform1;
	t_light l;

	transform1 = mat4x4_identity();

	color(&c, 0.8, 1.0, 0.6);
	m = default_material();
	m.color = c;
	m.diffuse = 0.7;
	m.specular = 0.2;
	sphere(&s1, NULL, 1.0, NULL);
	s1.material = m;
	world_add_object(world, &s1);

	m2 = default_material();
	transform1 = scaling(0.5, 0.5, 0.5);
	sphere(&s2, NULL, 1.0, &transform1);
	s2.material = m2;
	world_add_object(world, &s2);

	l = default_point_light();
	
	world_add_light(world, &l);
}

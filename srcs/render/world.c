/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:29:20 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/04 11:48:08 by melshafi         ###   ########.fr       */
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
	t_double4 center;
	t_mat4x4 scaling_matrix;
	t_color c;
	t_material m;

	color(&c, 0.8, 1.0, 0.6);
	m = material(&c, 0.1, 0.7, 0.2, 200.0);
	scaling_matrix = scaling(0.5, 0.5, 0.5);
	point(&center, 0.0, 0.0, 0.0);
	sphere(&s1, &center, 1.0, NULL);
	sphere(&s2, &center, 1.0, &scaling_matrix);
	s1.material = m;
	s2.material = m;
	world->objects[0] = s1;
	world->objects[1] = s2;
	world->num_objects = 2;
	world->lights[0] = default_point_light();
	world->num_lights = 1;
}

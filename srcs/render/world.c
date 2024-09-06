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
	t_object s3;
	t_double4 center;
	t_double4 center2;
	t_double4 center3;
	t_color c;
	t_color c2;
	t_color c3;
	t_material m;
	t_material m2;
	t_material m3;
	t_mat4x4 transform1;
	t_mat4x4 transform2;
	t_mat4x4 transform3;
	t_light l;

	transform1 = mat4x4_identity();
	transform2 = mat4x4_identity();
	transform3 = mat4x4_identity();

	color(&c, 1.0, 0.0, 0.0);
	m = material(&c, 0.1, 0.7, 0.4, 200.0);
	point(&center, -1.5, 0.0, 2.0);
	sphere(&s1, &center, 1.0, &transform1);
	s1.material = m;
	world_add_object(world, &s1);

	color(&c2, 0.0, 0.0, 1.0);
	m2 = material(&c2, 0.1, 0.7, 0.4, 200.0);
	point(&center2, 1.5, 0.0, 2.0);
	sphere(&s2, &center2, 1.0, &transform2);
	s2.material = m2;
	world_add_object(world, &s2);

	color(&c3, 0.0, 1.0, 0.0);
	m3 = material(&c3, 0.1, 0.7, 0.4, 200.0);
	point(&center3, 0.0, 2.0, 2.0);
	transform3 = scaling(0.5, 1.5, 1.0);
	sphere(&s3, &center3, 1.0, &transform3);
	s3.material = m3;
	world_add_object(world, &s3);

	l = default_point_light();
	// point(&l.position, -10.0, 10, -10.0);
	
	world_add_light(world, &l);
}

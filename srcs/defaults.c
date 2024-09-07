/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defaults.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:57:19 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/06 18:29:21 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	default_mat(t_mat *mat)
{
	cinit(&mat->c, 1, 1, 1);
	mat->amb = 0.1;
	mat->diff = 0.9;
	mat->spec = 0.9;
	mat->shiny = 200.0;
}

void	default_sphere(t_obj *sphere)
{
	static int	id = 1;
	t_mat		mat;
	t_mat4x4	identity = mat4x4_identity();

	default_mat(&mat);
	sphere->center = row4(0, 0, 0, 1);
	sphere->radius = 1.0;
	set_transform(sphere, &identity);
	sphere->material = mat;
	sphere->type = SPHERE;
	sphere->id = id;
	++id;
}

void	default_plane(t_obj *plane)
{
	static int	id = 1;
	t_mat		mat;
	const t_mat4x4 identity = mat4x4_identity();

	default_mat(&mat);
	point(&plane->center, 0, 0, 0);
	vector(&plane->pl_norm, 0.001, 1.02, 0.001);
	set_transform(plane, (t_mat4x4 *)&identity);
	plane->material = mat;
	plane->type = PLANE;
	plane->id = id;
	++id;
}

void	default_cylinder(t_obj *cy)
{
	static int	id = 1;

	cy->type = CYLINDER;
	point(&cy->center, 0, 0, 0);
	cy->id = id;
	default_mat(&cy->material);
	cy->transform = mat4x4_identity();
	cy->radius = 1.0;
	cy->cy_min = -INFINITY;
	cy->cy_max = INFINITY;
	cy->cy_closed = false;
}

void	default_world(t_world *world)
{
	t_mat4x4	transformation;

	transformation = scaling(0.5, 0.5, 0.5);
	default_sphere(&world->obj[0]);
	cinit(&world->obj[0].material.c, 0.8, 1.0, 0.6);
	world->obj[0].material.diff = 0.7;
	world->obj[0].material.spec = 0.2;
	default_sphere(&world->obj[1]);
	set_transform(&world->obj[1], &transformation);
	point(&world->plight.pos, -10, 10, -10);
	cinit(&world->plight.intensity, 1, 1, 1);
}

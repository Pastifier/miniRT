/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:40:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/03 16:09:55 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "intersection.h"

typedef struct s_world
{
	t_obj			obj[6];
	t_light			plight;
	t_intersections	xs;
}	t_world;

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		fov;
	double		aspect;
	double		half_view;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_mat4x4	transform;
}	t_webcam;

t_intersections	*intersect_world(t_world * world, t_ray *r);
void			prepare_computations(t_intersection *hit, t_ray *r);
t_color			shade_hit(t_world *world, t_intersection *hit);
t_color			color_at(t_world *world, t_ray *r);
t_mat4x4		view_transform(t_double4 *from, t_double4 *to, t_double4 *up);

t_webcam		init_camera(int hsize, int vsize, double fov);
t_ray			to_the_pixel_and_beyond(t_webcam *cam, int px, int py);
bool			is_shadowed(t_world *w, t_double4 *p);

#endif // !WORLD_H
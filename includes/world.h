/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:40:03 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 18:37:47 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "intersection.h"

typedef struct s_world
{
	t_obj			obj[3];
	t_light			plight;
	t_intersections	xs;
}	t_world;

t_intersections	*intersect_world(t_world * world, t_ray *r);
void			prepare_computations(t_intersection *hit, t_ray *r);
t_color			shade_hit(t_world *world, t_intersection *hit);
t_color			color_at(t_world *world, t_ray *r);

#endif // !WORLD_H
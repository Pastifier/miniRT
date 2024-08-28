/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:50 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 11:03:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vectors.h"
# include "ray.h"

typedef struct s_object
{
	t_vector3	origin;
	t_vector3	normal;
	double		t;
	bool		front_face;
	bool		(*hit)(struct s_object *obj, double ray_tmin, double ray_tmax, t_ray *ray);
	void		(*set_face_normal)(struct s_object *obj, t_ray *ray, t_vector3 *outward_normal);
}	t_object;

typedef struct s_sphere
{
	t_object	object;
	double		radius;
}	t_sphere;

#endif // !__OBJECTS_H

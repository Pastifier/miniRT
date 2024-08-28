/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:50 by melshafi          #+#    #+#             */
/*   Updated: 2024/08/28 13:16:31 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "ray.h"
# include <stdint.h>
# include <stdbool.h>

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
	AMBIENT_LIGHT
}	t_object_type;

typedef struct s_sphere
{
	double		radius;
}	t_sphere;

typedef struct s_plane
{
	double		width;
	double		height;
}	t_plane;

typedef struct s_cylinder
{
	double		radius;
	double		height;
}	t_cylinder;

typedef struct s_light
{
	double		intensity;
}	t_light;

typedef struct s_ambient_light
{
	double		intensity;
}	t_ambient_light;

typedef struct s_object
{
	int			type;
	t_vector3	origin;
	t_vector3	normal;
	double		t;
	bool		front_face;
	uint32_t	color;
	double		(*hit)(t_object *obj, double ray_tmin, double ray_tmax, t_ray *ray);
	void		(*set_face_normal)(t_object *obj, t_ray *ray, t_vector3 *outward_normal);
	union u_objects
	{
		struct s_sphere			sphere;
		struct s_plane			plane;
		struct s_cylinder		cylinder;
		struct s_light			light;
		struct s_ambient_light	ambient_light;
	}	u;
}	t_object;

t_object	create_sphere(t_vector3 center, double radius, uint32_t color);

#endif // !__OBJECTS_H

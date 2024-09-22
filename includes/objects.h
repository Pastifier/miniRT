/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:30:02 by melshafi          #+#    #+#             */
/*   Updated: 2024/09/12 22:32:56 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

#include "rtmath.h"
#include "matrix.h"

typedef enum	e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CUBE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_TRIANGLE
}	t_object_type;

typedef struct	s_light
{
	t_double4	position;
	t_color	color;

	union	u_type
	{
		struct	s_point
		{
			t_color	intensity;
		}	point;
		struct	s_spot
		{
			double	intensity;
		}	spot;
	}	type; // I don't think the union needs a tag, but changing it will require a bunch of refactoring, so we're keeping it this way for now <3
}	t_light;

/*
Subject asks for Ambient lighting, which is a ratio, and an RGB Color range
which will be the color of ambient lighting in the scene applied to the objects
in the given ambient lighting ratio.
*/
typedef struct	s_material
{
	t_color		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
}	t_material;

typedef struct	s_object
{
	t_double4	center;
	t_mat4x4	transform;
	t_material	material;
	int			type;

	union	u_object
	{
		struct	s_sphere
		{
			double	radius;
		}	sphere;

		struct	s_plane {
			t_double4	normal;
		}	plane;

		struct	s_cube {
			double	side_length;
		}	cube;
		struct s_cylinder
		{
			double	radius;
			double	min;
			double	max;
			bool	closed;
		}	cy;
	}	obj;
}	t_object;


typedef struct	s_discriminant
{
	double a;
	double b;
	double c;
	double disc;
	double sqrt_disc;
}	t_discriminant;

typedef struct s_ray
{
	t_double4		origin;
	t_double4		direction;
	t_intersections	itx;
}	t_ray;

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		field_of_view;
	t_mat4x4	transform;
	double		half_width;
	double		half_height;
	double		half_view;
	double		aspect_ratio;
	double		pixel_size;
}	t_camera;

typedef struct s_world
{
	int			num_objects;
	int			num_lights;
	t_object	objects[100];
	t_light		lights[100];
	t_mat4x4	cam_inverse;
}	t_world;

void			empty_world(t_world *world);
void			world_add_object(t_world *world, t_object *object);
void			world_add_light(t_world *world, t_light *light);
void			default_world(t_world *world);
void			setup_camera(t_camera *camera, double fov);
t_mat4x4		view_transform(t_double4 from, t_double4 to, t_double4 up);
t_ray			ray_for_pixel(t_camera *camera, int px, int py);

t_light			default_point_light(void);
t_material		default_material(void);
t_material		material(t_color *color, double ambient, double diffuse, double specular, double shininess);

bool			is_shadowed(t_world *world, t_double4 *point, t_light *light);
t_color			lighting(t_material *material, t_light *light, t_double4 *point, t_double4 *eye_v, t_double4 *normal, bool in_shadow);
t_double4		reflect(t_double4 *in, t_double4 *normal);
t_color			shade_hit(t_world *world, t_itx_computation *comps, int depth);
t_color			reflected_color(t_world *world, t_itx_computation *comps, int depth);
t_color			refracted_color(t_world *world, t_itx_computation *comps, int depth);
double			schlick(t_itx_computation *comps);

void			ray_create(t_ray *ray, t_double4 *origin, t_double4 *direction);
void			ray_position(t_double4 *result, t_ray *ray, double t);
void			ray_transform(t_ray *ray, t_mat4x4 *matrix);

void			sphere(t_object *sphere, t_double4 *center, double radius, t_mat4x4 *transform);
void			intersect_sphere(t_ray *ray, t_object *sphere, t_intersections *xs);
t_double4		sphere_normal_at(t_object *sphere, t_double4 *world_point);

void 			plane(t_object *plane, t_double4 *center, t_mat4x4 *transform);
t_double4		plane_normal_at(t_object *plane);
void			intersect_plane(t_ray *ray, t_object *plane, t_intersections *xs);

void			cube(t_object *cube, t_double4 *center, double length, t_mat4x4 *transform);
t_double4		cube_normal_at(t_object *cube, t_double4 *world_point);
void			intersect_cube(t_ray *ray, t_object *cube, t_intersections *xs);

#endif // !OBJECTS_H

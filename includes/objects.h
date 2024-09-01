#ifndef OBJECTS_H
# define OBJECTS_H

#include "rtmath.h"
#include "matrix.h"	

typedef enum	e_object_type
{
	OBJ_SPHERE
}	t_object_type;

typedef struct	s_point_light
{
	t_double4	position;
	t_color		intensity;
}	t_point_light;

typedef struct	s_material
{
	t_color		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
}	t_material;

typedef struct	s_sphere
{
	t_double4	center;
	double		radius;
	t_mat4x4	transform;
	t_material	material;
}	t_sphere;

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

t_point_light	default_light(void);
t_material		default_material(void);

t_color			lighting(t_material *material, t_point_light *light, t_double4 *point, t_double4 *eye_v, t_double4 *normal);
t_double4		reflect(t_double4 *in, t_double4 *normal);

void			ray_create(t_ray *ray, t_double4 *origin, t_double4 *direction);
void			ray_position(t_double4 *result, t_ray *ray, double t);
void			ray_transform(t_ray *ray, t_mat4x4 *matrix);

void			sphere(t_sphere *sphere, t_double4 *center, double radius, t_mat4x4 *transform);
void			intersect_sphere(t_ray *ray, t_sphere *sphere);
t_double4		sphere_normal_at(t_sphere *sphere, t_double4 *world_point);

#endif // !OBJECTS_H
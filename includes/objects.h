#ifndef OBJECTS_H
# define OBJECTS_H

#include "rtmath.h"
#include "matrix.h"	

typedef enum	e_object_type
{
	OBJ_SPHERE
}	t_object_type;

typedef struct	s_sphere
{
	t_double4	center;
	double		radius;
	t_mat4x4	transform;
	t_color		color;
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

void	ray_create(t_ray *ray, t_double4 *origin, t_double4 *direction);
void	ray_position(t_double4 *result, t_ray *ray, double t);
void	ray_transform(t_ray *ray, t_mat4x4 *matrix);

void	sphere(t_sphere *sphere, t_double4 *center, double radius, t_mat4x4 *transform);
void	intersect_sphere(t_ray *ray, t_sphere *sphere);

#endif // !OBJECTS_H
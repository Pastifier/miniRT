#include "objects.h"
#include "rtmath.h"
#include "linear_algebra.h"
#include "colors.h"

t_double4	reflect(t_double4 *in, t_double4 *normal)
{
	t_double4 result;
	double dot;

	dot = vdot(in, normal);
	d4mul(&result, normal, 2.0 * dot);
	d4sub(&result, in, &result);
	return (result);
}

t_material	default_material(void)
{
	t_material m;

	color(&m.color, 1.0, 1.0, 1.0);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}

t_point_light	default_light(void)
{
	t_point_light l;

	point(&l.position, -10.0, 10.0, -10.0);
	color(&l.intensity, 1.0, 1.0, 1.0);
	return (l);
}

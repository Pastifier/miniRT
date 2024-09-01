/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:30:20 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 13:32:25 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include "linear_algebra.h"
#include "matrix.h"
#include "libft.h"

#define MAX_INTERSECTIONS 200

#define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f, (%0.3f))\n", v.x, v.y, v.z, v.w)

void	set_transform(t_obj *obj, t_mat4x4 *m)
{
	ft_memcpy(&obj->transform, m, sizeof(*m));
}
bool	intersect_sphere(t_ray *r, t_obj *sphere, t_intersections *xs)
{
	t_double4	obj_to_ray;
	double		a;
	double		b;
	double		c;
	double		h;
	t_ray		ray2;
	t_mat4x4	inverse;

	inverse = mat4x4_inverse(&sphere->transform);
	ray2 = m4r_transform(r, &inverse);
	d4sub(&obj_to_ray, &sphere->center, &ray2.origin);
	a = vdot(&ray2.direction, &ray2.direction);
	b = -2.0 * vdot(&ray2.direction, &obj_to_ray);
	c = vdot(&obj_to_ray, &obj_to_ray) - (sphere->radius * sphere->radius);
	h = b * b - (4 * a * c);
	if (h < 0.0)
		return (false);
	h = sqrt(h);
	if (xs->count + 2 < MAX_INTERSECTIONS)
	{
		xs->arr[xs->count].obj = sphere;
		xs->arr[xs->count].t = (-b - h) / (2.0 * a);
		xs->arr[xs->count].got_hit = true;
		xs->arr[xs->count + 1].obj = sphere;
		xs->arr[xs->count + 1].t = (-b + h) / (2.0 * a);
		xs->arr[xs->count + 1].got_hit = true;
		xs->count += 2;
	}
	else
		/*deal with it*/ return (false);
	return (true);
}

t_intersection	*get_hit(t_intersections *xs)
{
	double	cmp;
	int		i;
	int		desired;

	i = 0;
	desired = 0;
	cmp = INFINITY;
	while (i < xs->count)
	{
		if (xs->arr[i].got_hit && xs->arr[i].t >= 0 && xs->arr[i].t < cmp)
		{
			cmp = xs->arr[i].t;
			desired = i;
		}
		i++;
	}
	if (isinf(cmp))
		return (NULL);
	return (&xs->arr[desired]);
}

t_double4	normal_at(t_obj *obj, t_double4 *world_p)
{
	t_double4	obj_n_p[2];
	t_double4	world_n;
	t_double4	origin;
	t_mat4x4	inv_trnsfrm;
	t_mat4x4	trnspoz_inv;

	point(&origin, 0, 0, 0);
	inv_trnsfrm = mat4x4_inverse(&obj->transform);
	trnspoz_inv = mat4x4_transpose(&inv_trnsfrm);
	obj_n_p[1] = mat4x4_cross_vec(&inv_trnsfrm, world_p);
	d4sub(&obj_n_p[0], &obj_n_p[1], &origin);
	world_n = mat4x4_cross_vec(&trnspoz_inv, &obj_n_p[0]);
	world_n.w = 0;
	vnormalize(&world_n);
	return (world_n);
}

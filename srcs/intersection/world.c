/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 08:54:15 by ebinjama          #+#    #+#             */
/*   Updated: 2024/09/01 23:35:16y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"
#include "linear_algebra.h"
#include "libft.h"
#include "colors.h"
#include "matrix.h"
#include <stdio.h>

void	prepare_computations(t_intersection *hit, t_ray *r)
{
	hit->p = position(r, hit->t);
	vector(&hit->eye, -r->direction.x, -r->direction.y, -r->direction.z);
	hit->s_normal = normal_at(hit->obj, &hit->p);
	if (vdot(&hit->s_normal, &hit->eye) < 0)
	{
		hit->inside = true;
		d4negate(&hit->s_normal);
	}
	else
		hit->inside = false;
}


// The naming for `t_mat` should definitely change, cuz it
// confused me when I was typing the paramater in due to 
// the existence of `t_mat4x4`.
t_color	shade_hit(t_world *world, t_intersection *hit)
{
	// you were trying to see whether you needed the hit or just
	// the intersection.
	return (lighting(&hit->obj->material, &world->plight, hit));
}

t_intersections	*intersect_world(t_world *world, t_ray *r)
{
	t_intersections	*xs = ft_calloc(1, sizeof(*xs));
	if (!xs) /*deal with it*/ return (NULL);

	for (int i = 0; i < 6; i++)
	{
		intersect_sphere(r, &world->obj[i], xs);
	}
	quick_sort_intersections(xs->arr, xs->count);
	return (xs);
}

//void	draw_sphere_using_rt(t_program *context, t_obj *sphere, t_light *plight)
//{
//	t_double4	ray_origin;
//	double		wall_z;
//	double		wall_size;
//	double		pixel_size;
//	double		half;
//	double		world_y;
//	double		world_x;
//	t_double4	pos;
//	t_double4	norm;
//	t_ray		r;
//	t_intersections	xs;
//	t_intersection	*hit;

//	point(&ray_origin, 0, 0, -5);
//	wall_z = 10;
//	wall_size = 7;
//	pixel_size = wall_size / WIN_WIDTH;
//	half = wall_size / 2;
//	for (int y = 0; y < WIN_HEIGHT; y++)
//	{
//		world_y = half - pixel_size * y;
//		for (int x = 0; x < WIN_WIDTH; x++)
//		{
//			world_x = -half + pixel_size * x;
//			point(&pos, world_x, world_y, wall_z);
//			d4sub(&norm, &pos, &ray_origin);
//			vnormalize(&norm);
//			r = ray(ray_origin, norm);
//			ft_bzero(&xs, sizeof(t_intersections));
//			intersect_sphere(&r, sphere, &xs);
//			hit = get_hit(&xs);
//			if (hit)
//			{
//				r.itx = position(&r, hit->t);
//				r.s_normal = normal_at(hit->obj, &r.itx);
//				vector(&r.eye, -r.direction.x, -r.direction.y, -r.direction.z);
//				r.c = lighting(&hit->obj->material, plight, &r.itx, &r);
//				put_pixel(&context->canvas, x, y, &r.c);
//			}
//		}
//	}
//	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr,
//		0, 0);
//}

t_color			color_at(t_world *world, t_ray *r)
{
	t_intersections	*xs;
	t_intersection	*hit;
	t_color			res;

	cinit(&res, 0, 0, 0);
	xs = intersect_world(world, r);
	if (!xs)
		/*deal with it*/ return (res.set.w = 0, res);
	hit = get_hit(xs);
	if (!hit)
		/*deal with it*/ return (res.set.w = 0, res);
	prepare_computations(hit, r);
	return (shade_hit(world, hit));
}

t_mat4x4	view_transform(t_double4 *from, t_double4 *to, t_double4 *up)
{
	t_double4	orient_vecs[3]; // lookat, left, true_up
	t_double4	upn;
	t_mat4x4	ori;
	t_mat4x4	translateit;

	d4sub(&orient_vecs[0], to, from);
	vnormalize(&orient_vecs[0]);
	vnorm(&upn, up);
	vcross(&orient_vecs[1], &orient_vecs[0], &upn);
	vcross(&orient_vecs[2], &orient_vecs[1], &orient_vecs[0]);
	ori.r1 = row4(orient_vecs[1].x, orient_vecs[1].y, orient_vecs[1].z, 0);
	ori.r2 = row4(orient_vecs[2].x, orient_vecs[2].y, orient_vecs[2].z, 0);
	ori.r3 = row4(-orient_vecs[0].x, -orient_vecs[0].y, -orient_vecs[0].z, 0);
	point(&ori.r4, 0, 0, 0); // , 1
	translateit = translation(-from->x, -from->y, -from->z);
	ori = mat4x4_cross(&ori, &translateit);
	return (ori);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 21:04:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/30 23:32:11y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "miniRT.h"
#include "macros.h"
#include "linear_algebra.h"
#include "intersection.h"
#include <stdio.h>
#include "matrix.h"
#include "libft.h"
#include "world.h"

t_color COLOR_RED;

#define PRINT_VECTOR(v) printf("(%0.3f, %0.3f, %0.3f, (%0.3f))\n", v.x, v.y, v.z, v.w)
#define PRINT_VECTOR_2D(v) printf("(%0.3f, %0.3f)\n", v.x, v.y);

#include "mlx.h"

void	fill_canvas(t_canvas *canvas, uint32_t color)
{
	int	i;

	i = 0;
	while (i < canvas->line_length * WIN_HEIGHT)
	{
		*(uint32_t *)(canvas->addr + i) = color;
		i += sizeof(uint32_t);
	}
}

void	draw_square(t_program *context, t_double4 coord, int w, int h)
{
	int	x;
	int	y;
	t_color color;

	cinit(&color, 1, 0, 0);
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(&context->canvas, coord.x + x, coord.y + y, &color);
			x++;
		}
		y++;
	}
}

void	draw_clock(t_program *context)
{
	double radius = (3.0 / 8.0) * WIN_WIDTH;
	double twelfth = M_PI / 6;
	t_double4 twelve = row4(0, radius, 0, 1);
	for (int i = 0; i < 12; i++)
	{
		m4d_rotate_z(&twelve, twelfth * (i + 1));
		m4d_translate(&twelve, WIN_WIDTH / 2, WIN_HEIGHT / 2, 0);
		PRINT_VECTOR(twelve);
		draw_square(context, twelve, 50, 50);
		point(&twelve, 0, radius, 0);
	}
}

//void draw_circle_using_rt(t_program *context, t_obj *sphere)
//{
//	t_double4 camera_origin = row4(0, 0, -5, 1);
//	double viewport_width = 2.0;
//	double viewport_height = 2.0 * (WIN_HEIGHT / (double)WIN_WIDTH);

//	for (int x = 0; x < WIN_WIDTH; x++)
//	{
//		for (int y = 0; y < WIN_HEIGHT; y++)
//		{
//			double u = (x + 0.5) * (viewport_width / WIN_WIDTH) - viewport_width / 2.0;
//			double v = (y + 0.5) * (viewport_height / WIN_HEIGHT) - viewport_height / 2.0;

//			t_double4 ray_direction = row4(u, v, 1.0, 0);

//			vnormalize(&ray_direction);

//			t_ray r = ray(camera_origin, ray_direction);
//			//PRINT_VECTOR(camera_origin);
//			//PRINT_VECTOR(ray_direction);
//			t_intersections xs = {0};
//			intersect_sphere(&r, sphere, &xs);
//			t_intersection *hit = get_hit(&xs);
//			if (hit)
//				put_pixel(&context->canvas, x, y, &COLOR_RED);
//		}
//	}
//}

void	draw_sphere_using_rt(t_program *context, t_obj *sphere, t_light *plight)
{
	t_double4	ray_origin;
	double		wall_z;
	double		wall_size;
	double		pixel_size;
	double		half;
	double		world_y;
	double		world_x;
	t_double4	pos;
	t_double4	norm;
	t_ray		r;
	t_intersections	xs;
	t_intersection	*hit;

	point(&ray_origin, 0, 0, -5);
	wall_z = 10;
	wall_size = 7;
	pixel_size = wall_size / WIN_WIDTH;
	half = wall_size / 2;
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		world_y = half - pixel_size * y;
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			world_x = -half + pixel_size * x;
			point(&pos, world_x, world_y, wall_z);
			d4sub(&norm, &pos, &ray_origin);
			vnormalize(&norm);
			r = ray(ray_origin, norm);
			ft_bzero(&xs, sizeof(t_intersections));
			intersect_sphere(&r, sphere, &xs);
			hit = get_hit(&xs);
			if (hit)
			{
				//r.itx = position(&r, hit->t);
				hit->p = position(&r, hit->t);
				hit->s_normal = normal_at(hit->obj, &hit->p);
				vector(&hit->eye, -r.direction.x, -r.direction.y, -r.direction.z);
				r.c = lighting(&hit->obj->material, plight, hit);
				put_pixel(&context->canvas, x, y, &r.c);
			}
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->canvas.ptr,
		0, 0);
}


void	default_mat(t_mat *mat)
{
	cinit(&mat->c, 1, 1, 1);
	mat->amb = 0.1;
	mat->diff = 0.9;
	mat->spec = 0.9;
	mat->shiny = 200.0;
}

t_mat4x4	IDENTITY_MATRIX;

void	default_sphere(t_obj *sphere)
{
	static int	id = 1;
	t_mat		mat;
	t_mat4x4	identity = mat4x4_identity();

	default_mat(&mat);
	sphere->center = row4(0, 0, 0, 1);
	sphere->radius = 1;
	set_transform(sphere, &identity);
	sphere->material = mat;
	sphere->type = SPHERE;
	sphere->id = id;
	++id;
}

void	default_world(t_world *world)
{
	t_mat4x4	transformation;

	transformation = scaling(0.5, 0.5, 0.5);
	default_sphere(&world->obj[0]);
	cinit(&world->obj[0].material.c, 0.8, 1.0, 0.6);
	world->obj[0].material.diff = 0.7;
	world->obj[0].material.spec = 0.2;
	default_sphere(&world->obj[1]);
	set_transform(&world->obj[1], &transformation);
	point(&world->plight.pos, -10, 10, -10);
	cinit(&world->plight.intensity, 1, 1, 1);
}

int main(void)
{
	t_world world;
	default_world(&world);

	t_ray r;
	point(&r.origin, 0, 0, 0.75);
	vector(&r.direction, 0, 0, -1);
	//t_intersections *xs = intersect_world(&world, &r);
	//t_intersection *hit = get_hit(xs);

	//point(&world.plight.pos, 0, 0.25, 0);

	//hit->t = 0.5;
	//hit->obj = &world.obj[1];
	//prepare_computations(hit, &r);
	world.obj[0].material.amb = 1;
	world.obj[1].material.amb = 1;

	//PRINT_VECTOR(shade_hit(&world, hit).set);

	PRINT_VECTOR(color_at(&world, &r).set);

	return (0);
}

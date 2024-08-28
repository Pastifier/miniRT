/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 11:46:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "rendering.h"
#include "minirt.h"
#include "mlx.h"
#include <stdio.h>

void	render(t_program *context)
{
	t_vector3	pixel_00;
	t_vector3	pixel_center;
	t_vector3	ray_direction;
	t_ray		ray;

	pixel_00 = vec3_add(context->camera.cartesian_upper_left,
			vec3_scaleby(vec3_add(context->camera.pixel_delta_u, context->camera.pixel_delta_v), 0.5));
	for (int x = 0; x < WIN_WIDTH; x++)
	{
		for (int y = 0; y < WIN_HEIGHT; y++)
		{
			pixel_00 = vec3_add(context->camera.cartesian_upper_left,
					vec3_add(vec3_scaleby(context->camera.pixel_delta_u, x),
						vec3_scaleby(context->camera.pixel_delta_v, y)));
			pixel_center = vec3_add(pixel_00, vec3_scaleby(vec3_add(context->camera.pixel_delta_u, context->camera.pixel_delta_v), 0.5));
			ray_direction = vec3_normal(vec3_subtract(pixel_center, context->camera.center));
			ray = (t_ray){context->camera.center, ray_direction};
			pixel_put(&context->img, (t_vector2){x, y}, ray_color(ray));
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->img.img, 0, 0);
}

//void	render(t_program *context)
//{
//	t_vector3	operations;
//	t_vector3	operations2;
//	t_vector3	graphical_penetration_point;
//	t_vector3	ray_direction;
//	t_camera	qomra;

//	qomra = context->camera;
//	for (int py = 0; py < WIN_HEIGHT; py++)
//	{
//		for (int px = 0; px < WIN_WIDTH; px++)
//		{
//			operations = vec3_scaleby(qomra.pixel_delta_u, px);
//			operations2 = vec3_scaleby(qomra.pixel_delta_v, py);
//			operations2 = vec3_add(operations, operations2);
//			graphical_penetration_point = vec3_add(qomra.cartesian_shift, operations2);
//			ray_direction = vec3_subtract(graphical_penetration_point, qomra.center);
//			pixel_put(&context->img,
//				(t_vector2){px, py},
//				ray_color((t_ray){qomra.center, ray_direction}));
//		}
//	}
//	mlx_put_image_to_window(context->mlx, context->win, context->img.img, 0, 0);
//}

// #define DBG_PRINT_FLT(i) printf("Line: %d, File: %s: %s = %0.2f\n", __LINE__, __FILE__, #i, i)
// void	render(t_program *context)
// {
// 	t_camera	cam;
// 	t_vector3	point_local;
// 	t_vector3	point;
// 	t_vector3	dir;
// 	float		tx;
// 	float		ty;

// 	cam = context->camera;
// 	for (int x = 0; x < WIN_WIDTH; x++)
// 	{
// 		for (int y = 0; y < WIN_HEIGHT; y++)
// 		{
// 			tx = (float)x / (WIN_WIDTH - 1);
// 			ty = (float)y / (WIN_HEIGHT - 1);
// 			point_local = vec3_add(cam.bottom_left_local, (t_vector3){cam.viewport_width * tx, cam.viewport_height * ty, 0});
// 			point = vec3_add(cam.center,
// 							vec3_add(vec3_scaleby(cam.right, point_local.x),
// 								vec3_add(vec3_scaleby(cam.up, point_local.y),
// 									vec3_scaleby(cam.lookat, point_local.z))));
// 			dir = vec3_normal(vec3_add(point, vec3_scaleby(cam.center, -1)));
// 			//DBG_PRINT_FLT(dir.z);
// 			// ray_color(whatever);
// 			pixel_put(&context->img, (t_vector2){x, y}, convert_to_color(dir.x, dir.y, dir.z));
// 		}
// 	}
// 	mlx_put_image_to_window(context->mlx, context->win, context->img.img, 0, 0);
// }

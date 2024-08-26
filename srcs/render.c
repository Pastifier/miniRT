/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:08:33 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/27 00:53:09 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "rendering.h"
#include "minirt.h"
#include "mlx.h"

void	render(t_program *context)
{
	t_vector3	operations;
	t_vector3	operations2;
	t_vector3	graphical_penetration_point;
	t_vector3	ray_direction;
	t_camera	qomra;

	qomra = context->camera;
	for (int py = 0; py < WIN_HEIGHT; py++)
	{
		for (int px = 0; px < WIN_WIDTH; px++)
		{
			operations = vec3_scaleby(qomra.pixel_delta_u, px);
			operations2 = vec3_scaleby(qomra.pixel_delta_v, py);
			operations2 = vec3_add(operations, operations2);
			graphical_penetration_point = vec3_add(qomra.cartesian_shift, operations2);
			ray_direction = vec3_subtract(graphical_penetration_point, qomra.center);
			pixel_put(&context->img,
				(t_vector2){px, py},
				ray_color((t_ray){qomra.center, ray_direction}));
		}
	}
	mlx_put_image_to_window(context->mlx, context->win, context->img.img, 0, 0);
}

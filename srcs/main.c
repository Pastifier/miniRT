/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:43:27 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 16:55:40 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "rendering.h"
#include "log.h"

int	main(int argc, char *argv[])
{
	static t_program	context;

	init_program(argc, argv, &context);
	t_vector3 viewport_upper_left = vec3_subtract(vec3_subtract(context.camera.origin, (t_vector3){0, 0, context.camera.focal_length}), vec3_subtract(vec3_scaleby(context.camera.viewport_u, 0.5), vec3_scaleby(context.camera.viewport_v, 0.5)));
	vec3_print(viewport_upper_left);
	t_vector3 pixel00_location = vec3_add(viewport_upper_left, vec3_scaleby(vec3_add(context.camera.pixel_delta_u, context.camera.pixel_delta_v), 0.5));
	pixel00_location.y = -pixel00_location.y;
	vec3_print(pixel00_location);
	for(int y = 0; y < WIN_HEIGHT; y++)
	{
		for(int x = 0; x < WIN_WIDTH; x++)
		{
			t_vector3 pixel_center = vec3_add(pixel00_location, vec3_add(vec3_scaleby(context.camera.pixel_delta_u, x), vec3_scaleby(context.camera.pixel_delta_v, y)));
			t_ray ray = (t_ray){context.camera.origin, vec3_subtract(pixel_center, context.camera.origin)};
			uint32_t color = ray_color(&ray);
			pixel_put(&context.img, (t_vector2){x, y}, color);
		}
	}
	mlx_put_image_to_window(context.mlx, context.win, context.img.img, 0, 0);
	mlx_loop(context.mlx);
	return (0);
}

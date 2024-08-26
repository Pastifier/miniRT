/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:43:27 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/26 12:36:33 by ebinjama         ###   ########.fr       */
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
	for (int j = 0; j < WIN_HEIGHT - 1; j++)
	{
		for (int i = 0; i < WIN_WIDTH; i++)
		{
			t_vector2 point = (t_vector2){i, j};
			pixel_put(&context.img, point, assign_color((j) / WIN_WIDTH - 1, (i) / WIN_HEIGHT - 1, 0));
			//mlx_pixel_put(context.mlx, context.win, j, i, 0x00FFFFFF);
		}
	}
	mlx_put_image_to_window(context.mlx, context.win, context.img.img, 0, 0);
	mlx_loop(context.mlx);
	return (0);
}

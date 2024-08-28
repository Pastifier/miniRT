/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 10:43:27 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/28 14:06:04 by melshafi         ###   ########.fr       */
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
	render(&context);
	mlx_key_hook(context.win, move_camera, &context);
	mlx_loop(context.mlx);
	return (0);
}

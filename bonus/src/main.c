/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:32 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/04 20:19:18 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "miniRT.h"
#include "mlx.h"

int	main(int argc, char *argv[])
{
	(void)argc; (void)argv;
	t_program	context;

	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	// create_canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	// setup_hooks(...);
	// render_frame(&context);
	 mlx_loop(context.mlx);
	return (0);
}
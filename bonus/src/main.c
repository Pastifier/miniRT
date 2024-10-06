/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:32 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/06 18:59:40 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "miniRT.h"
#include "mlx.h"

int	main(int argc, char *argv[])
{
	(void)argc; (void)argv;
	t_program	context;

	if (argc > 2 || argc == 1)
		return (write(2, "Usage:\n\t./miniRT <filename>.rt", 31), 2);
	// parse_file(argv[1]);
	context.mlx = mlx_init();
	context.win = mlx_new_window(context.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	// create_canvas(&context, WIN_WIDTH, WIN_HEIGHT);
	// setup_hooks(...);
	// update loop:
	mlx_loop(context.mlx);
	return (0);
}

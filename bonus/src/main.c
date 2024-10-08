/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:35:32 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/07 06:14:48 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "macros.h"
#include "miniRT.h"
#include "mlx.h"
#include <stdlib.h> // for `exit(3)`
#include <unistd.h> // for `write(2)`
#include "libft.h"

void	init_mlx(t_program *context);
bool	init_obj_arr(t_program *context);

int	main(int argc, char *argv[])
{
	(void)argc; (void)argv;
	t_program	context;

	if (argc != 2)
		return ((void)write(2, "Usage:\n\t./miniRT <filename>.rt\n", 32), 2);
	context = (t_program){0};
	if (!init_obj_arr(&context))
	{
		ft_putendl_fd("FATAL: Couldn't allocate for necessary objects.", 2);
		return (2);
	}
	if (!parse_file(argv[1], &context))
		return (destroy_world(&context), 2);
	init_mlx(&context);
	// setup_hooks(...);
	// update loop:
	mlx_loop(context.mlx);
	return (0);
}

void	init_mlx(t_program *context)
{
	context->mlx = mlx_init();
	if (!context->mlx)
	{
		write(2, "FATAL: error initialising minilibx.", 36);
		exit(2);
	}
	context->win = mlx_new_window(\
		context->mlx, \
		WIN_WIDTH, \
		WIN_HEIGHT, \
		"miniRT" \
	);
	if (!create_canvas(context, WIN_WIDTH, WIN_HEIGHT))
	{
		mlx_destroy_window(context->mlx, context->win);
		free(context->mlx);
		exit(2);
	}
}

bool	init_obj_arr(t_program *context)
{
	context->world.lights = ft_calloc(_RT_MAX_LIGHTS_, sizeof(t_light));
	if (!context->world.lights)
		return (false);
	context->world.shapes = ft_calloc(_RT_MAX_SHAPES_, sizeof(t_obj));
	if (!context->world.shapes)
	{
		free(context->world.lights);
		return (false);
	}
	return (true);
}

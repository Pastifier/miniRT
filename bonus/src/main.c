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
#include "keys.h"

void	_rt_start(t_program *context);
bool	init_obj_arr(t_program *context);

//extern int	update(void *param);
//extern int	destroy_program(t_program *context);
//extern int	check_state(void *context);
//extern int	check_key_presses(int keysym, void *context);

int	main(int argc, char *argv[])
{
	t_program	context;

	if (argc != 2)
	{
		write(2, "Usage:\n\t./miniRT <filename>.rt\n", 32);
		return (2);
	}
	context = (t_program){0};
	context.mlx = mlx_init();
	if (!context.mlx)
	{
		write(2, "FATAL: error initialising minilibx.", 36);
		exit(2);
	}
	if (!init_obj_arr(&context))
	{
		ft_putendl_fd("FATAL: Couldn't allocate for necessary objects.", 2);
		return (2);
	}
	if (!parse_file(argv[1], &context))
		return (destroy_world(&context), 2);
	if (!pool_init(&context))
	{
		destroy_world(&context);
		destroy_mlx(&context);
		ft_putendl_fd("FATAL: Couldn't allocate for threads.", 2);
		return (2);
	}
	_rt_start(&context);
	return (0);
}

void	_rt_start(t_program *context)
{
	//context->mlx = mlx_init();
	//if (!context->mlx)
	//{
	//	write(2, "FATAL: error initialising minilibx.", 36);
	//	exit(2);
	//}
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
	context->selected = (struct s_select){.is_cam = true, .object = NULL};
	mlx_hook(context->win, ON_KEYDOWN, 1L, &check_key_presses, context);
	mlx_hook(context->win, ON_KEYUP, 1L << 1, &check_key_releases, context);
	mlx_hook(context->win, ON_DESTROY, 1L >> 2, &destroy_program, context);
	mlx_mouse_hook(context->win, &check_mouse_clicks, context);
	mlx_loop_hook(context->mlx, &check_state, context);
	mlx_loop(context->mlx);
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
		free(context->world.shapes);
		return (false);
	}
	context->textures = ft_calloc(1, sizeof(t_list));
	return (true);
}

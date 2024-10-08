/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:22:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/09 02:06:52 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"

bool		parse_light(t_program *context, t_split *fields, int curr_line)
{
	t_world	*world;
	char	*next;
	float	temp;

	context->flt_operations = 0;
	world = &context->world;
	if (world->num_lights >= _RT_MAX_LIGHTS_)
	{
		ft_putstr_fd("Warning: Maximum number of lights: ", 2);
		ft_putnbr_fd(_RT_MAX_LIGHTS_, 2);
		ft_putendl_fd(" has been reached. Ignoring line...", 2);
		return (str_arr_destroy(fields->array), false);
	}
	if (fields->wordcount < 3)
	{
		ft_putstr_fd("Error: Invalid format for Ambient Light on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	next = fields->array[1];
	temp = ft_atof(next, context);
	if (context->runtime_error == 2 && *(next + context->flt_operations + (temp < 0) - 1) != ',')
	{
		ft_putstr_fd("Error: Invalid format for Light Object on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	world->lights[world->num_lights].pos.x = temp;
	temp = ft_atof((next += context->flt_operations + (temp <= -0.f)), context);
	if (context->runtime_error == 2 && *(next - 1) != ',')
	{
		ft_putstr_fd("Error: Invalid format for Light Object on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	context->flt_operations = 0;
	world->lights[world->num_lights].pos.y = temp;
	temp = ft_atof((next += context->flt_operations + (temp <= -0.f)), context);
	if (context->runtime_error == 2 && *(next - 1) != ',')
	{
		ft_putstr_fd("Error: Invalid format for Light Object on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tL <x>,<y>,<z> <ratio> [<R>,<G>,<B>]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	context->flt_operations = 0;
	world->lights[world->num_lights].pos.z = temp;
	world->lights[world->num_lights++].pos.w = 1;
	return (true);
}

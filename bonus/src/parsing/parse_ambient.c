/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:26:43 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/09 04:07:00 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static bool	get_ambient_color(t_program *context, t_split *fields,
				int curr_line);
bool	parse_ambient(t_program *context, t_split *fields, int curr_line)
{
	if (context->ambiance.is_set)
	{
		ft_putstr_fd("Error on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putstr_fd(": Ambient light already set on line ", 2);
		ft_putnbr_fd(context->ambiance.line_set, 2);
		ft_putendl_fd(". Aborting...", 2);
		return (str_arr_destroy(fields->array), false);
	}
	if (fields->wordcount != 3)
	{
		ft_putstr_fd("Error: Invalid format for Ambient Light ratio on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tA <ratio> <R>,<G>,<B>", 2);
		return (str_arr_destroy(fields->array), false);
	}
	context->ambiance.ratio = ft_atof(fields->array[1], context);
	if (context->runtime_error == 2)
	{
		ft_putstr_fd("Error: Invalid format for Ambient Light ratio on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected: valid floating-point number.", 2);
		return (str_arr_destroy(fields->array), false);
	}
	if (context->ambiance.ratio < -0.f || context->ambiance.ratio > 1.f)
	{
		ft_putstr_fd("Error: Invalid value for Ambient Light ratio on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected: floating-point value in range [0.0, 1.0]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	return (get_ambient_color(context, fields, curr_line));
}

bool	get_ambient_color(t_program *context, t_split *fields, int curr_line)
{
	char	*next;
	t_eint	rgb;

	context->ambiance.color.a = 1 * (_RT_OS_MACOS_ == 0);
	rgb = ft_atoi(fields->array[2]);
	if (rgb.error && *(fields->array[2] + rgb.operations + (rgb.value < 0)) != ',')
	{
		ft_putstr_fd("Error: Invalid format for Ambient Light on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tA <ratio> <R>,<G>,<B>", 2);
		return (str_arr_destroy(fields->array), false);
	}
	if (rgb.value > 255 || rgb.value < 0)
	{
		ft_putstr_fd("Error: Invalid value for Ambient Light red component on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected: integer value within range [0, 255]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	context->ambiance.color.r = rgb.value / 255.999;
	rgb = ft_atoi((next = fields->array[2] + rgb.operations + 1 + (rgb.value < 0)));
	if (rgb.error && *(next - 1) != ',')
	{
		ft_putstr_fd("Error: Invalid format for Ambient Light on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tA <ratio> <R>,<G>,<B>", 2);
		return (str_arr_destroy(fields->array), false);
	}
	if (rgb.value > 255 || rgb.value < 0)
	{
		ft_putstr_fd("Error: Invalid value for Ambient Light green component on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected: integer value within range [0, 255]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	context->ambiance.color.g = rgb.value / 255.999;
	rgb = ft_atoi((next += rgb.operations + 1 + (rgb.value < 0)));
	if (rgb.error && *(next - 1) != ',')
	{
		ft_putstr_fd("Error: Invalid format for Ambient Light on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected:\n\tA <ratio> <R>,<G>,<B>", 2);
		return (str_arr_destroy(fields->array), false);
	}
	if (rgb.value > 255 || rgb.value < 0)
	{
		ft_putstr_fd("Error: Invalid value for Ambient Light blue component on line ", 2);
		ft_putnbr_fd(curr_line, 2);
		ft_putendl_fd(". Expected: integer value within range [0, 255]", 2);
		return (str_arr_destroy(fields->array), false);
	}
	context->ambiance.color.b = rgb.value / 255.999;
	color_clamp(&context->ambiance.color);
	context->ambiance.is_set = true;
	context->ambiance.line_set = curr_line;
	return (str_arr_destroy(fields->array), true);
}

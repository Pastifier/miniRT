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
		return (parse_fatal_msg(ERR_AMBIENT_DEFINED, curr_line),
			str_arr_destroy(fields->array), false);
	if (fields->wordcount != 3)
		return (parse_err_msg(ERR_AMBIENT_FORMAT, ERR_EXPECT_TYPE_A,
			curr_line), str_arr_destroy(fields->array), false);
	context->ambiance.ratio = ft_atof(fields->array[1], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_AMBIENT_FORMAT, ERR_EXPECT_TYPE_A,
			curr_line), str_arr_destroy(fields->array), false);
	if (context->ambiance.ratio < -0.f || context->ambiance.ratio > 1.f)
		return (parse_err_msg(ERR_AMBIENT_VALUE, ERR_EXPECT_FLOAT_RANGE,
			curr_line), str_arr_destroy(fields->array), false);
	return (get_ambient_color(context, fields, curr_line));
}

bool	get_ambient_color(t_program *context, t_split *fields, int curr_line)
{
	char	*next;
	t_eint	rgb;

	context->ambiance.color.a = 1 * (_RT_OS_MACOS_ == 0);
	rgb = ft_atoi(fields->array[2]);
	if (rgb.error && *(fields->array[2] + rgb.operations + (rgb.value < 0)) != ',')
		return (parse_err_msg(ERR_AMBIENT_FORMAT, ERR_EXPECT_TYPE_A,
			curr_line), str_arr_destroy(fields->array), false);
	if (rgb.value > 255 || rgb.value < 0)
		return (parse_err_msg(ERR_AMBIENT_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
			curr_line), str_arr_destroy(fields->array), false);
	context->ambiance.color.r = rgb.value / 255.999;
	rgb = ft_atoi((next = fields->array[2] + rgb.operations + 1 + (rgb.value < 0)));
	if (rgb.error && *(next - 1) != ',')
		return (parse_err_msg(ERR_AMBIENT_FORMAT, ERR_EXPECT_TYPE_A,
			curr_line), str_arr_destroy(fields->array), false);
	if (rgb.value > 255 || rgb.value < 0)
		return (parse_err_msg(ERR_AMBIENT_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
			curr_line), str_arr_destroy(fields->array), false);
	context->ambiance.color.g = rgb.value / 255.999;
	rgb = ft_atoi((next += rgb.operations + 1 + (rgb.value < 0)));
	if (rgb.error && *(next - 1) != ',')
		return (parse_err_msg(ERR_AMBIENT_FORMAT, ERR_EXPECT_TYPE_A,
			curr_line), str_arr_destroy(fields->array), false);
	if (rgb.value > 255 || rgb.value < 0)
		return (parse_err_msg(ERR_AMBIENT_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
			curr_line), str_arr_destroy(fields->array), false);
	context->ambiance.color.b = rgb.value / 255.999;
	color_clamp(&context->ambiance.color);
	context->ambiance.is_set = true;
	context->ambiance.line_set = curr_line;
	return (str_arr_destroy(fields->array), true);
}

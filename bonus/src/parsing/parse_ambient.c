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
	if (!parse_color(&context->ambiance.color, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	context->ambiance.is_set = true;
	context->ambiance.line_set = curr_line;
	return (str_arr_destroy(fields->array), true);
}

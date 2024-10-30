/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/30 16:11:55 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_vec4(t_vec4s *vec, char *str, t_program *context, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
		return (parse_err_msg(ERR_VEC4_FORMAT, ERR_EXPECT_TUPLE, curr_line),
			false);
	vec->x = ft_atof(split.array[0], context);
	if (context->runtime_error == 2)
		return (parse_fatal_msg(ERR_EXPECT_FLOAT, curr_line), false);
	vec->y = ft_atof(split.array[1], context);
	if (context->runtime_error == 2)
		return (parse_fatal_msg(ERR_EXPECT_FLOAT, curr_line), false);
	vec->z = ft_atof(split.array[2], context);
	if (context->runtime_error == 2)
		return (parse_fatal_msg(ERR_EXPECT_FLOAT, curr_line), false);
	vec->w = 1.0f;
	return (str_arr_destroy(split.array), true);
}

bool	parse_color(t_color *color, char *str, t_program *context,
	int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
		return (parse_err_msg(ERR_COLOR_FORMAT, ERR_EXPECT_TYPE_C, curr_line),
			false);
	color->r = ft_atof(split.array[0], context);
	if (context->runtime_error == 2)
		return (parse_fatal_msg(ERR_EXPECT_FLOAT, curr_line), false);
	color->r = color->r / 255.999;
	color->g = ft_atof(split.array[1], context);
	if (context->runtime_error == 2)
		return (parse_fatal_msg(ERR_EXPECT_FLOAT, curr_line), false);
	color->g = color->g / 255.999;
	color->b = ft_atof(split.array[2], context);
	if (context->runtime_error == 2)
		return (parse_fatal_msg(ERR_EXPECT_FLOAT, curr_line), false);
	color->b = color->b / 255.999;
	if (color->r < 0.0f || color->g < 0.0f || color->b < 0.0f
		|| color->r > 1.0f || color->g > 1.0f || color->b > 1.0f)
		return (parse_err_msg(ERR_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
				curr_line), false);
	color->a = (_RT_OS_MACOS_ == 0);
	str_arr_destroy(split.array);
	return (true);
}

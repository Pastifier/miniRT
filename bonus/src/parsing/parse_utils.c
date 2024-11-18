/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/18 14:31:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_vec4p(t_vec4s *vec, char *str, t_program *context, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
		return (parse_err_msg(ERR_VEC4_FORMAT, ERR_EXPECT_TUPLE, curr_line),
			false);
	vec->x = ft_atof(split.array[0], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_FLOAT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	vec->y = ft_atof(split.array[1], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_FLOAT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	vec->z = ft_atof(split.array[2], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_FLOAT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	vec->w = 1.0f;
	return (str_arr_destroy(split.array), true);
}

bool	parse_vec4v(t_vec4s *vec, char *str, t_program *context, int curr_line)
{
	t_split	split;

	split = ft_split(str, ",");
	if (split.wordcount != 3)
		return (parse_err_msg(ERR_VEC4_FORMAT, ERR_EXPECT_TUPLE, curr_line),
			false);
	vec->x = ft_atof(split.array[0], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_FLOAT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	vec->y = ft_atof(split.array[1], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_FLOAT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	vec->z = ft_atof(split.array[2], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_FLOAT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	vec->w = 0.0f;
	return (str_arr_destroy(split.array), true);
}

bool	parse_single_f(float *f, char *str, t_program *context, int curr_line)
{
	*f = ft_atof(str, context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
			false);
	return (true);
}

bool	check_final_color_range(t_color *color, int curr_line)
{
	if (color->r < 0.0f || color->g < 0.0f || color->b < 0.0f
		|| color->r > 1.0f || color->g > 1.0f || color->b > 1.0f)
		return (parse_err_msg(ERR_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
				curr_line), false);
	color->a = (_RT_OS_MACOS_ == 0);
	return (true);
}

bool	parse_color(t_color *color, char *str, int curr_line)
{
	t_split	split;
	t_eint	color_int;

	split = ft_split(str, ",\n\r");
	if (split.wordcount != 3)
		return (parse_err_msg(ERR_COLOR_FORMAT, ERR_EXPECT_COLOR_FORMAT,
				curr_line), false);
	color_int = ft_atoi(split.array[0]);
	if (color_int.error)
		return (parse_err_msg(ERR_COLOR_VALUE, ERR_EXPECT_INT,
				curr_line), false);
	color->r = color_int.value / 255.999;
	color_int = ft_atoi(split.array[1]);
	if (color_int.error)
		return (parse_err_msg(ERR_COLOR_VALUE, ERR_EXPECT_INT,
				curr_line), false);
	color->g = color_int.value / 255.999;
	color_int = ft_atoi(split.array[2]);
	if (color_int.error)
		return (parse_err_msg(ERR_COLOR_VALUE, ERR_EXPECT_INT,
				curr_line), false);
	color->b = color_int.value / 255.999;
	if (!check_final_color_range(color, curr_line))
		return (str_arr_destroy(split.array), false);
	return (str_arr_destroy(split.array), true);
}

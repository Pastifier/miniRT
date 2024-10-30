/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:22:24 by ebinjama          #+#    #+#             */
/*   Updated: 2024/10/16 13:10:35 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool		parse_light_color(const t_split *fields, int curr_line, t_world *world);

bool		parse_light(t_program *context, const t_split *fields, int curr_line)
{
	t_world	*world;
	float	temp;

	world = &context->world;
	if (world->num_lights >= _RT_MAX_LIGHTS_)
		return (parse_warn_msg(ERR_MAX_LIGHTS, curr_line),
			str_arr_destroy(fields->array), true);
	if (fields->wordcount < 3)
		return (parse_err_msg(ERR_LIGHT_FORMAT, ERR_EXPECT_TYPE_L,
			curr_line), str_arr_destroy(fields->array), false);
	if (!parse_vec4(&world->lights[world->num_lights].pos, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	temp = ft_atof(fields->array[2], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_LIGHT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	if (temp < -0.f || temp > 1.f)
		return (parse_err_msg(ERR_LIGHT_VALUE, ERR_EXPECT_FLOAT_RANGE, curr_line),
			str_arr_destroy(fields->array), false);
	world->lights[world->num_lights].ratio = temp;
	if (fields->wordcount == 4)
		return (parse_light_color(fields, curr_line, world));
	world->num_lights++;
	return (str_arr_destroy(fields->array), true);
}

bool		parse_light_color(const t_split *fields, int curr_line, t_world *world)
{
	char	*next;
	t_eint	rgb;

	world->lights[world->num_lights].color.a = 1 * (_RT_OS_MACOS_ == 0);
	rgb = ft_atoi(fields->array[3]);
	if (rgb.error && *(fields->array[3] + rgb.operations + (rgb.value < 0)) != ',')
		return (parse_err_msg(ERR_LIGHT_FORMAT, ERR_EXPECT_TYPE_L, curr_line),
			str_arr_destroy(fields->array), false);
	if (rgb.value > 255 || rgb.value < 0)
		return (parse_err_msg(ERR_LIGHT_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
			curr_line), str_arr_destroy(fields->array), false);
	world->lights[world->num_lights].color.r = rgb.value / 255.999;
	rgb = ft_atoi((next = fields->array[3] + rgb.operations + 1 + (rgb.value < 0)));
	if (rgb.error && *(next - 1) != ',')
		return (parse_err_msg(ERR_LIGHT_FORMAT, ERR_EXPECT_TYPE_L, curr_line),
			str_arr_destroy(fields->array), false);
	if (rgb.value > 255 || rgb.value < 0)
		return (parse_err_msg(ERR_LIGHT_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE, curr_line),
			str_arr_destroy(fields->array), false);
	world->lights[world->num_lights].color.g = rgb.value / 255.999;
	rgb = ft_atoi((next += rgb.operations + 1 + (rgb.value < 0)));
	if (rgb.error && *(next - 1) != ',')
		return (parse_err_msg(ERR_LIGHT_FORMAT, ERR_EXPECT_TYPE_L, curr_line),
			str_arr_destroy(fields->array), false);
	if (rgb.value > 255 || rgb.value < 0)
		return (parse_err_msg(ERR_LIGHT_COLOR_VALUE, ERR_EXPECT_COLOR_RANGE,
			curr_line), str_arr_destroy(fields->array), false);
	world->lights[world->num_lights].color.b = rgb.value / 255.999;
	color_clamp(&world->lights[world->num_lights++].color);
	return (str_arr_destroy(fields->array), true);
}

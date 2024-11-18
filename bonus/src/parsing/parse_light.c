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

bool	parse_spot_light_color(const t_split *fields, int curr_line,
			t_world *world, t_program *context)
{
	t_light	*light;
	t_color	parsed_color;

	light = &world->lights[world->num_lights];
	if (!parse_single_f(&light->ratio, fields->array[3], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (light->ratio < -0.f || light->ratio > 1.f)
		return (parse_err_msg(ERR_LIGHT_VALUE, ERR_EXPECT_FLOAT_RANGE,
				curr_line),
			str_arr_destroy(fields->array), false);
	if (!parse_single_f(&light->specs.spot.spot_angle, fields->array[4],
			context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (light->specs.spot.spot_angle < -0.f || light->specs.spot.spot_angle
		> 90.f)
		return (parse_err_msg(ERR_LIGHT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	light->specs.spot.spot_angle *= ((float)M_PI / 180.f);
	if (!parse_color(&parsed_color,
			fields->array[5], curr_line))
		return (str_arr_destroy(fields->array), false);
	color_scaleby(&light->specs.spot.intensity, \
		&parsed_color, light->ratio);
	return (true);
}

bool	parse_spot_light(t_program *context, const t_split *fields,
			int curr_line)
{
	t_light	*light;

	light = &context->world.lights[context->world.num_lights];
	if (context->world.num_lights >= _RT_MAX_LIGHTS_)
		return (parse_warn_msg(ERR_MAX_LIGHTS, curr_line, true),
			str_arr_destroy(fields->array), true);
	if (fields->wordcount != 6)
		return (parse_err_msg(ERR_LIGHT_FORMAT, ERR_EXPECT_TYPE_SL,
				curr_line), str_arr_destroy(fields->array), false);
	if (!parse_vec4p(&light->pos, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!parse_vec4v(&light->specs.spot.orientation, fields->array[2],
			context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!parse_spot_light_color(fields, curr_line, &context->world, context))
		return (str_arr_destroy(fields->array), false);
	if (!is_normalised(light->specs.spot.orientation))
		light->specs.spot.orientation = lag_vec4s_normalize_highp(
				light->specs.spot.orientation);
	light->type = SPOT_LIGHT;
	context->world.num_lights++;
	return (str_arr_destroy(fields->array), true);
}

bool	parse_point_light_color(const t_split *fields, int curr_line,
			t_world *world)
{
	t_light	*curr_light;
	t_color	parsed_color;

	curr_light = &world->lights[world->num_lights];
	if (!parse_color(&parsed_color,
			fields->array[3], curr_line))
		return (str_arr_destroy(fields->array), false);
	color_scaleby(&curr_light->specs.point.intensity, \
		&parsed_color, curr_light->ratio);
	world->num_lights++;
	return (true);
}

bool	parse_light(t_program *context, const t_split *fields, int curr_line)
{
	t_light	*light;
	float	temp;

	light = &context->world.lights[context->world.num_lights];
	if (context->world.num_lights >= _RT_MAX_LIGHTS_)
		return (parse_warn_msg(ERR_MAX_LIGHTS, curr_line, true),
			str_arr_destroy(fields->array), true);
	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_LIGHT_FORMAT, ERR_EXPECT_TYPE_L,
				curr_line), str_arr_destroy(fields->array), false);
	if (!parse_vec4p(&light->pos, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	temp = ft_atof(fields->array[2], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_LIGHT_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	if (temp < -0.f || temp > 1.f)
		return (parse_err_msg(ERR_LIGHT_VALUE, ERR_EXPECT_FLOAT_RANGE,
				curr_line),
			str_arr_destroy(fields->array), false);
	light->ratio = temp;
	if (!parse_point_light_color(fields, curr_line, &context->world))
		return (str_arr_destroy(fields->array), false);
	light->type = POINT_LIGHT;
	return (str_arr_destroy(fields->array), true);
}

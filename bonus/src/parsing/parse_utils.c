/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:22:29 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/31 13:09:39 by melshafi         ###   ########.fr       */
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

bool	parse_single_f(float *f, char *str, t_program *context, int curr_line)
{
	*f = ft_atof(str, context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line), false);
	return (true);
}

static inline void extract_rot_around_axis(t_mat4s *m, const t_vec4s _axs, float _theta)
{
	lag_vec4sv_init(&m->r1, cosf(_theta) + _axs.x * _axs.x * (1 - cosf(_theta)),
		_axs.x * _axs.y * (1 - cosf(_theta)) - _axs.z * sinf(_theta),
		_axs.x * _axs.z * (1 - cosf(_theta)) + _axs.y * sinf(_theta)
	);
	lag_vec4sv_init(&m->r2, _axs.x * _axs.y * (1 - cos(_theta)) + _axs.z * sinf(_theta),
		cosf(_theta) + _axs.y * _axs.y * (1 - cosf(_theta)),
		_axs.y * _axs.z * (1 - cosf(_theta)) - _axs.x * sinf(_theta)
	);
	lag_vec4sv_init(&m->r3, _axs.z * _axs.x * (1 - cosf(_theta)) - _axs.y * sinf(_theta),
		_axs.z * _axs.y * (1 - cosf(_theta)) + _axs.x * sinf(_theta),
		cosf(_theta) + _axs.z * _axs.z * (1 - cosf(_theta))
	);
	lag_vec4sp_init(&m->r4, 0.f, 0.f, 0.f);
}

/// @param u Normalized orientation vector.
/// @warning At the risk of being repetitive, `u` must be a normalized vector!!
t_mat4s	rt_extract_rot_vertical(const t_vec4s u)
{
	const t_vec4s	j_hat = lag_vec4sv_ret(0.f, 1.f, 0.f);
	t_vec4s			rot_axis;
	float			theta;
	t_mat4s			ret;

	if (u.x == 0 && fabsf(u.y - 1) < EPSILON && u.z == 0)
		return (lag_mat4s_rotation_x(0));
	if (u.x == 0 && fabsf(u.y + 1) < EPSILON && u.z == 0)
		return (lag_mat4s_rotation_x(-M_PI));
	rot_axis = lag_vec4s_cross_ret(j_hat, u);
	rot_axis = lag_vec4s_normalize_highp(rot_axis);
	theta = acosf(lag_vec4s_dot_ret(u, j_hat));
	extract_rot_around_axis(&ret, rot_axis, theta);
	return (ret);
}

bool	is_normalised(t_vec4s vec)
{
	float	mag;

	lag_vec4s_magnitude(&mag, vec);
	if (fabsf(mag - 1.0f) > EPSILON)
		return (false);
	return (true);
}

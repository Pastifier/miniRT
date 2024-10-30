/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:14:10 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/30 16:09:03 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_sphere(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	sp;

	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_SP,
			curr_line), str_arr_destroy(fields->array), false);
	sp.type = SPHERE;
	if (!parse_vec4(&sp.trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	sp.specs.radius = ft_atof(fields->array[2], context) / 2.0f;
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	if (!parse_color(&sp.color, fields->array[3], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	//Set scale, rot, and orientation to default values
	sp.scale = lag_vec4s_ret(1, 1, 1, 1);
	sp.rot = lag_mat4s_identity();
	sp.inv_transform = lag_mat4s_get_transform_inverse(sp.rot, sp.scale.simd, sp.trans.simd);
	context->world.shapes[context->world.num_shapes++] = sp;
	str_arr_destroy(fields->array);
	return (true);
}

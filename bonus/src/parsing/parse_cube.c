/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:04 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/18 15:44:45 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static void	material_init(t_material *material, const t_split *fields,
	t_program *context, int curr_line)
{
	__m128	color_vec;

	color_vec = material->color.v.simd;
	material->xordc = \
		(t_color){.v.simd = _mm_xor_ps(color_vec, color_vec)};
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->sheen = 200;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
	if (fields->wordcount == 7 && parse_material(material, &fields->array[5],
			context, curr_line))
		return ;
}

bool	parse_cube(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*cu;

	if (context->world.num_shapes == _RT_MAX_SHAPES_)
		return (str_arr_destroy(fields->array),
			parse_warn_msg(ERR_MAX_SHAPES, NULL, curr_line, true), true);
	cu = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount < 5 || fields->wordcount > 7)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CU,
				curr_line), str_arr_destroy(fields->array), false);
	cu->type = CUBE;
	if (!parse_vec4p(&cu->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!parse_vec4v(&cu->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	cu->specs.side_length = ft_atof(fields->array[3], context);
	if (!parse_color(&cu->material.color, fields->array[4], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&cu->material, fields, context, curr_line);
	cu->scale = lag_vec4s_ret(1, 1, 1, 1);
	cu->rot = rt_extract_rot_vertical(cu->orientation);
	cu->inv_transform = lag_mat4s_get_transform_inverse(cu->rot,
			cu->scale.simd, cu->trans.simd);
	return (str_arr_destroy(fields->array), true);
}

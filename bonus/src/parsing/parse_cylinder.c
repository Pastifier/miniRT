/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:38:59 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/20 14:06:47 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"
#include <assert.h>

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
	if (fields->wordcount == 8 && parse_material(material, &fields->array[6],
			context, curr_line))
		return ;
}

bool	get_cylinder_extras(t_obj *cy, t_program *context,
		const t_split *fields, int curr_line)
{
	float	height;

	cy->radius = ft_atof(fields->array[3], context) / 2.0f;
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	height = ft_atof(fields->array[4], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	cy->specs.min = -height / 2.0f;
	cy->specs.max = height / 2.0f;
	cy->specs.closed = true;
	if (!parse_color(&cy->material.color, fields->array[5], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&cy->material, fields, context, curr_line);
	cy->scale = lag_vec4s_ret(cy->radius, height / 2.f, cy->radius, 1);
	cy->rot = rt_extract_rot_vertical(cy->orientation);
	cy->inv_transform = lag_mat4s_get_transform_inverse(cy->rot,
			cy->scale.simd, cy->trans.simd);
	lag_mat4s_transpose(&cy->inv_transform, &cy->transposed_inverse);
	return (true);
}

//Radius does not affect the cylinder (Investigate)
bool	parse_cylinder(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*cy;

	if (context->world.num_shapes == _RT_MAX_SHAPES_)
		return (str_arr_destroy(fields->array),
			parse_warn_msg(ERR_MAX_SHAPES, NULL, curr_line, true), true);
	cy = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount < 6 || fields->wordcount > 8)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CY ERR_ECY,
				curr_line), str_arr_destroy(fields->array), false);
	cy->type = CYLINDER;
	if (!parse_vec4p(&cy->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!parse_vec4v(&cy->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	is_normalised(&cy->orientation, curr_line);
	if (!get_cylinder_extras(cy, context, fields, curr_line))
		return (false);
	return (str_arr_destroy(fields->array), true);
}

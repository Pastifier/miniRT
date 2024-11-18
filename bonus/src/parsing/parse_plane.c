/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:08:31 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/18 13:20:13 by melshafi         ###   ########.fr       */
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
	if (fields->wordcount == 6 && parse_material(material, &fields->array[4],
			context, curr_line))
		return ;
}

bool	parse_plane(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*pl;

	if (context->world.num_shapes == _RT_MAX_SHAPES_)
		return (parse_warn_msg(ERR_MAX_SHAPES, curr_line, true), true);
	pl = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount < 4 || fields->wordcount > 6)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_PL,
				curr_line), str_arr_destroy(fields->array), false);
	pl->type = PLANE;
	pl->center.w = 1.f;
	if (!parse_vec4p(&pl->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!parse_vec4v(&pl->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!is_normalised(pl->orientation))
		pl->orientation = lag_vec4s_normalize_highp(pl->orientation);
	if (!parse_color(&pl->material.color, fields->array[3], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&pl->material, fields, context, curr_line);
	pl->scale = lag_vec4s_ret(1, 1, 1, 1);
	pl->rot = rt_extract_rot_vertical(pl->orientation);
	pl->inv_transform = lag_mat4s_get_transform_inverse(pl->rot,
			pl->scale.simd, pl->trans.simd);
	lag_mat4s_transpose(&pl->inv_transform, &pl->transposed_inverse);
	return (str_arr_destroy(fields->array), true);
}

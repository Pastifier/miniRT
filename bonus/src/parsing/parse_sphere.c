/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:14:10 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/06 15:59:04 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static void	material_init(t_material *material)
{
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->sheen = 200;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
}

bool	parse_sphere(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*sp;

	if (context->world.num_shapes == _RT_MAX_SHAPES_)
		return (parse_warn_msg(ERR_MAX_SHAPES, curr_line, true), true);
	sp = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_SP,
			curr_line), str_arr_destroy(fields->array), false);
	sp->type = SPHERE;
	if (!parse_vec4(&sp->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	sp->radius = ft_atof(fields->array[2], context) / 2.0f;
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
			str_arr_destroy(fields->array), false);
	if (!parse_color(&sp->material.color, fields->array[3], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&sp->material);
	sp->scale.simd = _mm_set1_ps(sp->radius);
	sp->scale.w = 1.f;
	//sp->scale = lag_vec4s_ret(1, 1, 1, 1);
	sp->rot = lag_mat4s_identity();
	sp->inv_transform = lag_mat4s_get_transform_inverse(sp->rot, sp->scale.simd, sp->trans.simd);
	lag_mat4s_transpose(&sp->inv_transform, &sp->transposed_inverse);
	str_arr_destroy(fields->array);
	return (true);
}

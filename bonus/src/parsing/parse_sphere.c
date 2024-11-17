/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:14:10 by melshafi          #+#    #+#             */
/*   Updated: 2024/11/17 06:06:53 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

static void	material_init(t_material *material, const t_split *fields, t_program *context, int curr_line)
{
	const __m128	color_vec = material->color.v.simd;

	material->xordc = \
		(t_color){.v.simd = _mm_xor_ps(color_vec, color_vec)};
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->sheen = 200;
	material->reflective = 0.0;
	material->transparency = 0.0;
	material->refractive_index = 1.0;
	if (fields->wordcount == 6 && parse_material(material, &fields->array[4], context, curr_line))
		return ;
}

bool	parse_sphere(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*sp;

	if (context->world.num_shapes == _RT_MAX_SHAPES_)
		return (parse_warn_msg(ERR_MAX_SHAPES, curr_line, true), true);
	sp = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount < 4 || fields->wordcount > 6)
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
	material_init(&sp->material, fields, context, curr_line);
	sp->scale.simd = _mm_set1_ps(sp->radius);
	sp->scale.w = 1.f;
	sp->rot = lag_mat4s_identity();
	sp->inv_transform = lag_mat4s_get_transform_inverse(sp->rot, sp->scale.simd, sp->trans.simd);
	lag_mat4s_transpose(&sp->inv_transform, &sp->transposed_inverse);
	sp->tex = rt_xpm_file_to_canvas("gravel_normal.xpm", context->mlx);
	return (str_arr_destroy(fields->array), true);
}

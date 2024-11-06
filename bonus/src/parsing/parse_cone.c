#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"
#include <assert.h>

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

bool	parse_cone(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*co;
	float	height;

	if (context->world.num_shapes == _RT_MAX_SHAPES_)
		return (parse_warn_msg(ERR_MAX_SHAPES, curr_line, true), true);
	co = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount != 6)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CY, curr_line),
				str_arr_destroy(fields->array), false);
	co->type = CONE;
	if (!parse_vec4(&co->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	if (!parse_vec4(&co->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	co->orientation.w = 0;
	if (!is_normalised(co->orientation))
		co->orientation = lag_vec4s_normalize_highp(co->orientation);
	co->radius = ft_atof(fields->array[3], context) / 2.0f;
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
				str_arr_destroy(fields->array), false);
	height = ft_atof(fields->array[4], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
				str_arr_destroy(fields->array), false);
	co->specs.min = -height / 2.0f;
	co->specs.max = height / 2.0f;
	co->specs.closed = true;//false;
	if (!parse_color(&co->material.color, fields->array[5], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&co->material);
	co->scale = lag_vec4s_ret(co->radius, height, co->radius, 1);
	co->rot = rt_extract_rot_vertical(co->orientation);
	co->inv_transform = lag_mat4s_get_transform_inverse(co->rot, co->scale.simd, co->trans.simd);
	return (str_arr_destroy(fields->array), true);
}

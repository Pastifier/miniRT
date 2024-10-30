#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool parse_cylinder(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*cy;
	float	height;

	cy = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount != 6)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CY, curr_line),
				str_arr_destroy(fields->array), false);
	cy->type = CYLINDER;
	if (!parse_vec4(&cy->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	// 1. Need to check that orientation is normalised (use normalize_highp())
	// 2. Need to convert it into a rotation matrix.
	if (!parse_vec4(&cy->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	cy->orientation.w = 0;
	cy->specs.radius = ft_atof(fields->array[3], context) / 2.0f;
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
				str_arr_destroy(fields->array), false);
	height = ft_atof(fields->array[4], context);
	if (context->runtime_error == 2)
		return (parse_err_msg(ERR_OBJ_VALUE, ERR_EXPECT_FLOAT, curr_line),
				str_arr_destroy(fields->array), false);
	cy->specs.min = -height / 2.0f;
	cy->specs.max = height / 2.0f;
	if (!parse_color(&cy->color, fields->array[5], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	cy->scale = lag_vec4s_ret(1, 1, 1, 1);
	cy->rot = lag_mat4s_identity(); ////
	cy->inv_transform = lag_mat4s_get_transform_inverse(cy->rot, cy->scale.simd, cy->trans.simd);
	return (str_arr_destroy(fields->array), true);
}

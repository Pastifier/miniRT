#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_plane(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*pl;

	pl = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_PL,
			curr_line), str_arr_destroy(fields->array), false);
	pl->type = PLANE;
	if (!parse_vec4(&pl->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	// 1. Need to check that orientation is normalised (use normalize_highp())
	// 2. Need to convert it into a rotation matrix.
	if (!parse_vec4(&pl->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	pl->orientation.w = 0;
	if (!parse_color(&pl->color, fields->array[3], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	pl->scale = lag_vec4s_ret(1, 1, 1, 1);
	pl->rot = lag_mat4s_identity(); ////
	pl->inv_transform = lag_mat4s_get_transform_inverse(pl->rot, pl->scale.simd, pl->trans.simd);
	return (str_arr_destroy(fields->array), true);
}

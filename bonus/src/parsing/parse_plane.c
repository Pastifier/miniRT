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
	if (!parse_vec4(&pl->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	pl->orientation.w = 0;
	if (!is_normalised(pl->orientation))
		pl->orientation = lag_vec4s_normalize_highp(pl->orientation);
	if (!parse_color(&pl->material.color, fields->array[3], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&pl->material);
	pl->scale = lag_vec4s_ret(1, 1, 1, 1);
	pl->rot = rt_extract_rot_vertical(pl->orientation);
	pl->inv_transform = lag_mat4s_get_transform_inverse(pl->rot, pl->scale.simd, pl->trans.simd);
	lag_mat4s_transpose(&pl->inv_transform, &pl->transposed_inverse);
	return (str_arr_destroy(fields->array), true);
}

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

//Radius does not affect the cylinder (Investigate)
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
	if (!parse_vec4(&cy->orientation, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	cy->orientation.w = 0;
	if (!is_normalised(cy->orientation))
		cy->orientation = lag_vec4s_normalize_highp(cy->orientation);
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
	cy->specs.closed = true;//false;
	if (!parse_color(&cy->material.color, fields->array[5], curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&cy->material);
	cy->scale = lag_vec4s_ret(cy->radius, height, cy->radius, 1);
	cy->rot = rt_extract_rot_vertical(cy->orientation);
	cy->inv_transform = lag_mat4s_get_transform_inverse(cy->rot, cy->scale.simd, cy->trans.simd);
	lag_mat4s_transpose(&cy->inv_transform, &cy->transposed_inverse);
	// (void)debug;
	return (str_arr_destroy(fields->array), true);
}

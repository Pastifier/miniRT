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

bool parse_cube(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	*cu;

	cu = &context->world.shapes[context->world.num_shapes++];
	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CU,
			curr_line), str_arr_destroy(fields->array), false);
	cu->type = CUBE;
	if (!parse_vec4(&cu->trans, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	cu->specs.side_length = ft_atof(fields->array[2], context);
	if (!parse_color(&cu->material.color, fields->array[3], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	material_init(&cu->material);
	cu->scale = lag_vec4s_ret(1, 1, 1, 1);
	cu->rot = lag_mat4s_identity();
	return (str_arr_destroy(fields->array), true);
}

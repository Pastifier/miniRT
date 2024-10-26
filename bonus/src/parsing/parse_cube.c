#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool parse_cube(t_program *context, t_split *fields, int curr_line)
{
	t_obj	cu;
	t_vec4s	*vec;
	t_color	*c;

	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CU,
			curr_line), str_arr_destroy(fields->array), false);
	cu.type = CUBE;
	vec = parse_vec4(fields->array[1], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	cu.trans = *vec;
	cu.specs.side_length = ft_atof(fields->array[2], context);
	c = parse_color(fields->array[3], context, curr_line);
	if (!c)
		return (str_arr_destroy(fields->array), false);
	cu.color = *c;
	//Set scale, rot, and orientation to default values
	cu.scale = lag_vec4s_ret(1, 1, 1, 1);
	cu.rot = lag_mat4s_identity();
	cu.orientation = lag_vec4s_ret(0, 0, 0, 0);
	context->world.shapes[context->world.num_shapes++] = cu;
	str_arr_destroy(fields->array);
	return (true);
}
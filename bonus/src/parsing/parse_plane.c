#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_plane(t_program *context, const t_split *fields, int curr_line)
{
	t_obj	pl;
	t_vec4s	vec;
	t_color	c;

	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_PL,
			curr_line), str_arr_destroy(fields->array), false);
	pl.type = PLANE;
	if (!parse_vec4(&vec, fields->array[1], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	pl.trans = vec;
	if (!parse_vec4(&vec, fields->array[2], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	pl.orientation = vec;
	if (!parse_color(&c, fields->array[3], context, curr_line))
		return (str_arr_destroy(fields->array), false);
	pl.color = c;
	//Set scale and rot to default values
	pl.scale = lag_vec4s_ret(1, 1, 1, 1);
	pl.rot = lag_mat4s_identity();
	context->world.shapes[context->world.num_shapes++] = pl;
	str_arr_destroy(fields->array);
	return (true);
}
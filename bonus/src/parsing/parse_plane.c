#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_plane(t_program *context, t_split *fields, int curr_line)
{
	t_obj	pl;
	t_vec4s	*vec;
	t_color	*c;

	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_PL,
			curr_line), str_arr_destroy(fields->array), false);
	pl.type = PLANE;
	vec = parse_vec4(fields->array[1], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	pl.trans = *vec;
	vec = parse_vec4(fields->array[2], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	pl.orientation = *vec;
	c = parse_color(fields->array[3], context, curr_line);
	if (!c)
		return (str_arr_destroy(fields->array), false);
	pl.color = *c;
	context->world.shapes[context->world.num_shapes++] = pl;
	str_arr_destroy(fields->array);
	return (true);
}
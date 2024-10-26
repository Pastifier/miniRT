#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool parse_cylinder(t_program *context, t_split *fields, int curr_line)
{
	t_obj	cy;
	t_vec4s	*vec;
	t_color	*c;
	float	height;

	if (fields->wordcount != 6)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_CY, curr_line),
				str_arr_destroy(fields->array), false);
	cy.type = CYLINDER;
	vec = parse_vec4(fields->array[1], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	cy.trans = *vec;
	vec = parse_vec4(fields->array[2], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	cy.orientation = *vec;
	cy.specs.radius = ft_atof(fields->array[3], context) / 2.0f;
	height = ft_atof(fields->array[4], context);
	cy.specs.min = -height / 2.0f;
	cy.specs.max = height / 2.0f;
	c = parse_color(fields->array[5], context, curr_line);
	if (!c)
		return (str_arr_destroy(fields->array), false);
	cy.color = *c;
	//Set scale and rot to default values
	sp.scale = lag_vec4s_ret(1, 1, 1, 1);
	sp.rot = lag_mat4s_identity();
	context->world.shapes[context->world.num_shapes++] = cy;
	str_arr_destroy(fields->array);
	return (true);
}
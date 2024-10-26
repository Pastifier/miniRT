/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:14:10 by melshafi          #+#    #+#             */
/*   Updated: 2024/10/22 14:14:14 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "macros.h"
#include "libft.h"
#include "colors.h"

bool	parse_sphere(t_program *context, t_split *fields, int curr_line)
{
	t_obj	sp;
	t_vec4s	*vec;
	t_color	*c;

	if (fields->wordcount != 4)
		return (parse_err_msg(ERR_OBJ_FORMAT, ERR_EXPECT_TYPE_SP,
			curr_line), str_arr_destroy(fields->array), false);
	sp.type = SPHERE;
	vec = parse_vec4(fields->array[1], context, curr_line);
	if (!vec)
		return (str_arr_destroy(fields->array), false);
	sp.trans = *vec;
	sp.specs.radius = ft_atof(fields->array[2], context) / 2.0f;
	c = parse_color(fields->array[3], context, curr_line);
	if (!c)
		return (str_arr_destroy(fields->array), false);
	sp.color = *c;
	//Set scale, rot, and orientation to default values
	sp.scale = lag_vec4s_ret(1, 1, 1, 1);
	sp.rot = lag_mat4s_identity();
	sp.orientation = lag_vec4s_ret(0, 0, 0, 0);
	context->world.shapes[context->world.num_shapes++] = sp;
	str_arr_destroy(fields->array);
	return (true);
}
